#!/usr/bin/env python
#author:geeksword
#blog:http://onestraw.net
#date:2014-9-30
'''
使用python2.7编写一个网站爬虫程序，支持参数如下：

spider.py -u url -d deep -f logfile -l loglevel(1-5)  --testself -thread number --dbfile  filepath  --key=”HTML5”

参数说明：

-u 指定爬虫开始地址

-d 指定爬虫深度

--thread 指定线程池大小，多线程爬取页面，可选参数，默认10

--dbfile 存放结果数据到指定的数据库（sqlite）文件中

--key 页面内的关键词，获取满足该关键词的网页，可选参数，默认为所有页面

-l 日志记录文件记录详细程度，数字越大记录越详细，可选参数，默认spider.log

--testself 程序自测，可选参数
'''
import os
import sys
import optparse
import urllib2
#import codecs
import Queue
import threading
import re
import logging
import sqlite3 as db
import doctest
from bs4 import BeautifulSoup


#全局变量
default={'url':'http://onestraw.net','deep':1,\
		'logfile':'spider.log','loglevel':'5',\
		'threads':10,'dbfile':'sqlite3','key':None}

dbfile=None
logger=None
logfile=None
loglevel=0
EXCEPT_LEVEL=1
RECORD_LEVEL=3
IGNORE_LEVEL=5

visited=set()
max_depth=0
key=None
page_dir=u'default_html'

TIMEOUT=10 #获取分配任务的等待时间,单位s
URLOPEN_TIMEOUT=3 #打开URL的等待时间,单位s

mutex=threading.Lock() #数据库操作互斥锁

#函数和类

def get_logger():
	u'''
	get,set and return the logger
	'''
	global logfile
	global logger
	logger = logging.getLogger('onestraw.spider')
	logger.setLevel(logging.INFO)
	formatter = logging.Formatter('%(name)-12s %(asctime)s '\
					'%(filename)s[line:%(lineno)d] '\
					'%(levelname)-8s %(message)s', '%a, %d %b %Y %H:%M:%S',)
	file_handler = logging.FileHandler(logfile)  
	file_handler.setFormatter(formatter)   
	logger.addHandler(file_handler)

	stream_handler = logging.StreamHandler(sys.stderr) 
	logger.addHandler(stream_handler) 
	

def islog(msglevel):
	u'''
	根据消息级别msglevel和用户指定的日志详细级别loglevel \
			来判断一条消息msg是否写入日志
	'''
	global loglevel
	if msglevel <= loglevel:
		return 1
	return 0

def create_table(table_name='WebPage'):
	u'''
	create a table to store web page in sqlite3
	'''
	global dbfile
	global logger
	try:
		conn = db.connect(dbfile)
		cursor = conn.cursor()

		sql='''create table if not exists %s(
			id integer primary key autoincrement, 
			title TEXT,
			url TEXT,
			content, TEXT)''' %(table_name)
		cursor.execute(sql)
		conn.commit()
	except Exception, e:
		if islog(EXCEPT_LEVEL):
			logger.error(e)
			logger.error(u'在数据库中创建表失败.')
	finally:
		cursor.close()
		conn.close()
#urlparse 模块会解析出各个模板
def save_page(url_name, url, content, cont2db):
	u'''
	保存一个网页到数据库中
	保存的内容：url_name, url, content
	content: ascii str
	cont2db: unicode
	'''
	global dbfile
	global logger
	global page_dir
	global mutex

	#store into file
	fout = open(page_dir+'/'+url_name+'.html','w')
	fout.write(content)
	fout.close()

	#store the page into db
	mutex.acquire()
	try:
		conn = db.connect(dbfile)
		cursor = conn.cursor()

		#print type(content) #<type,'unicode'>
		cursor.execute(u'''insert into WebPage(title, url, content) 
				values(?, ?, ?)''' ,(unicode(url_name), \
						unicode(url), unicode(cont2db)))
		conn.commit()
		cursor.close()
		conn.close()
	except Exception,e:
		if islog(EXCEPT_LEVEL):
			logger.error(e)
			logger.error(u'存储网页'+url+u'失败')
			logger.error(u'数据库插入数据失败')

	mutex.release()
	
def get_links(soup_page):
	u'''
	输出一个网页page
	返回一个url列表[(title,link),(title,link),...]
	'''
	url_list=[]
	links = list(soup_page.findAll('a'))
	pattern = re.compile(r'href="(http://[^"]*)".*>(.*)<')
	for link in links:
		new_url = pattern.search(unicode(link))
		if not new_url:
			continue
		if new_url.lastindex==2:
			new_url_name = new_url.group(2)
		else:
			new_url_name = new_url.group(1)[7:]
		new_url_name = ''.join(new_url_name.split())#del space
		new_url = new_url.group(1)
		url_list.append((new_url_name,new_url))
	return url_list

def has_key(page, key):
	u'''
	判断一个页面page是否含有关键词key
	'''
	#print 'in has_key()...)'
	cont = ''.join(page.split())
	regex = r'.*?%s.*?' %key
	pattern = re.compile(regex)
	if not key or pattern.search(cont):
		return 1
	return 0

def crawl_one(para_list):
	u'''
	爬取并处理一个网页
	'''
	global logger
	global visited
	global max_depth

	url, url_name, cur_depth, worker_pool=para_list #解析参数
	if url in visited:
		if islog(IGNORE_LEVEL):
			logger.info(u'该URL已经访问过:'+url)
		return
	visited.add(url)

	if islog(RECORD_LEVEL):
		logger.info(u'正在抓取分析:'+url)
	try:
		page = urllib2.urlopen(url)
	except Exception,e:
		if islog(EXCEPT_LEVEL):
			logger.error(e)
			logger.error(u"打开URL失败:"+url)
		return
	cont = page.read()
	soup = BeautifulSoup(cont)
	#get all url from url
	if cur_depth<=max_depth:
		links = get_links(soup)
		for (new_url_name, new_url) in links:
			worker_pool.add_task(crawl_one,[new_url, new_url_name, cur_depth+1])
	#store the page into db
	if has_key(soup.text, key):
		if islog(RECORD_LEVEL):
				logger.info('%s has key: %s' %(url, key))
		save_page(url_name, url, cont, soup.text)
		if islog(RECORD_LEVEL):
			logger.info(u'网页抓取保存完成:'+url)
	else:
		if islog(RECORD_LEVEL):
			logger.info('%s has no key: %s' %(url, key))
	logger.debug(u'剩余任务数:%d' %worker_pool.work_queue.qsize())

class Worker(threading.Thread):
	u'''
	任务执行者
	'''
	def __init__(self, work_queue):
		super(Worker,self).__init__()
		self.work_queue = work_queue
		self.start()
	def run(self):
		global logger
		while True:
			try:
				(func, args)=self.work_queue.get(block=True, timeout=TIMEOUT)
				func(args)
				self.work_queue.task_done()
			except Exception, e:
				if islog(EXCEPT_LEVEL):
					logger.error(e)
				break
class WorkerThreadPool(object):
	u'''
	实现了线程池
	'''
	def __init__(self, tasks, thread_num=2):
		self.work_queue = Queue.Queue()
		self.threads = []
		self._init_work_queue(tasks)
		self._init_thread_pool(thread_num)

	'''初始化工作队列'''
	def _init_work_queue(self, tasks): 
		for task in tasks:
			self.add_task(crawl_one, task)

	'''初始化线程池'''		
	def _init_thread_pool(self, thread_num):
		for i in xrange(thread_num):
			self.threads.append(Worker(self.work_queue))

	'''添加一项任务'''
	def add_task(self, func, args):
		args.append(self)
		self.work_queue.put((func, list(args)))
	'''查看剩余队列任务'''
	def task_left(self):
		return self.work_queue.qsize()

	'''等待所有线程运行完毕'''
	def wait_all_complete(self):
		for t in self.threads:
			if t.isAlive():
				t.join()

def crawl(url, thread_num):
	u'''
	url: 起始URL
	deep: 爬取深度
	爬虫主框架
	显示爬取进度：每10s显示一次已经抓取的网页个数和队列中等待抓取的URL数目
	'''
	global logger
	get_logger()
	create_table()
	
	worker_pool = WorkerThreadPool([[url,"initial_page", 1]] ,thread_num)
	worker_pool.wait_all_complete()


def show_default():
	'''
	show default value of all parameters
	>>> show_default()
	dbfile : sqlite3
	thread : 1
	url : http://onestraw.net
	deep : 2
	loglevel : 5
	key : geeksword
	logfile : spider.log
	
	'''
	default_str='\n'.join([' : '.join([str(k),str(default[k])]) for k in default])
	print default_str

def test_self():
	'''
	program self-test
	anther way: python -m doctest -v spider.py
	'''
	print doctest.testmod(verbose=True)

def main():
	'''start point'''
	parser = optparse.OptionParser()
	parser.add_option('-u','--url',action='store',\
			dest='url', default=default['url'],\
			help=u'指定爬虫开始地址')
	parser.add_option('-d','--deep',action='store',\
			dest='deep',default=default['deep'],\
			help=u'指定爬虫深度')
	parser.add_option('-f','--logfile',action='store',\
			dest='logfile',default=default['logfile'],\
			help=u'指定日志记录文件')
	parser.add_option('-l','--loglevel',action='store',\
			dest='loglevel', default=default['loglevel'],\
			help=u'''(1~5)日志记录文件记录详细程度，\
					数字越大记录越详细，默认为5''')
	parser.add_option('--dbfile', action='store',\
			dest='dbfile',default=default['dbfile'],\
			help=u'存放结果数据到指定的数据库（sqlite）文件中')
	parser.add_option('--thread',action='store',\
			dest='threads',default=default['threads'],\
			help=u'指定线程池大小，多线程爬取页面')
	parser.add_option('--key',action='store',\
			dest='key',default=default['key'],\
			help=u'页面内的关键词，获取满足该关键词的网页，可选参数，默认为所有页面')
	parser.add_option('--testself', action='store_true',\
			dest='testself',help=u'程序自测')
		
	parser.add_option('--default', action='store_true',\
			dest='default',help=u'显示参数的默认值')

	options,args = parser.parse_args(sys.argv)
	first_msg=u'onestraw.spider开始运行...'
	
	if islog(RECORD_LEVEL):
		logger.info(first_msg)
	
	if options.testself:
		test_self()
		return
	if options.default:
		show_default()
		return
	
	global loglevel
	global logfile
	global dbfile
	global max_depth
	global key
	global page_dir
	loglevel = int(options.loglevel)
	logfile = options.logfile
	dbfile = options.dbfile
	max_depth = int(options.deep)

	if options.key:
		key = options.key.decode('gb2312')
		page_dir = key
	if not os.path.exists(page_dir):
		os.mkdir(page_dir)
	crawl(options.url, int(options.threads))

if __name__=='__main__':
	main()
