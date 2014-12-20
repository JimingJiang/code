# -*- coding: utf-8 -*-
# python 2.7.6
#author: GeekSword
#site: http://onestraw.net
'''
功能：间隔固定时间提示休息
使用格式：
	python rest.py 间隔时间(单位:分钟)
'''
import os, sys, string, time, random
import cPickle
import pygame
'''
定义一个课间音乐类，每隔一段时间放一首歌
'''
class RestMusic():
	def __init__(self, intervals=45):
		self.PLAY_LISTS_FILENAME='playlist.pk'
		self.intervals = intervals
		self.playList=[]
	'''
	功能：列出一个目录下的所有文件，不包括目录
	rootDir: 输入目录
	'''
	def ListAllMusic(self, rootDir):
		if os.path.exists(rootDir):
			for files in os.listdir(rootDir):
				filename = os.path.join(rootDir,files)
				if not os.path.isdir(filename):
					print filename
	'''
	功能:手动添加歌曲至播放列表，保存至pk文件
	rootDir:歌曲目录
	'''
	def AddPlayList(self):
		print(u"请输入歌曲目录:")
		rootDir = sys.stdin.readline()
		rootDir = rootDir[0:len(rootDir)-1]
		if os.path.isdir(rootDir):
			self.ListAllMusic(rootDir)
		fp = open(self.PLAY_LISTS_FILENAME, 'wb')
		print(u"输入所配置歌曲目录下的文件名, 输入0结束")
		while 1:
			file = sys.stdin.readline()
			if len(file)==2 and file[0]=='0':
				break;
			filename = os.path.join(rootDir,file)
			cPickle.dump(filename[0:len(filename)-1],fp)
		fp.close()
	'''
	功能：从pk文件中读取播放列表
	'''
	def ReadFromPlayList(self):
		if not os.path.exists(self.PLAY_LISTS_FILENAME):
			print(u"播放列表文件不存在，请配置:")
			self.AddPlayList()
		fp = open(self.PLAY_LISTS_FILENAME, 'rb')
		try:
			while 1:
				self.playList.append(cPickle.load(fp))
		except EOFError:
			print "load finish"
		fp.close()
	'''
	功能：播放一首歌曲
	'''
	def PlayMusic(self, musicFile):
		pygame.mixer.init()
		pygame.mixer.music.load(musicFile)
		pygame.mixer.music.play()
		time.sleep(4*60)  #每首歌曲播放4分钟
		pygame.mixer.music.stop()
	'''
	从播放列表随机播放一首歌曲
	'''
	def RandomPlay(self):
		if len(self.playList) == 0:
			self.ReadFromPlayList()
		try:
			musicNum = len(self.playList)
			rnum = random.randint(0, musicNum-1)
			print(u"正播放%s" %self.playList[rnum])
			self.PlayMusic(self.playList[rnum])
		except IndexError as e:
			print(e)
			sys.exit(1)
	'''
	运行
	'''
	def run(self):
		while 1:
			self.RandomPlay()
			time.sleep(self.intervals*60)
#main
if __name__=='__main__':
	if len(sys.argv)==2:
		interval = string.atoi(sys.argv[1])
		rm = RestMusic(interval)
	else:
		rm = RestMusic()
	rm.run()
	