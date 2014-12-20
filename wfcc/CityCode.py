'''
author:亮剑
site:http://onestraw.net
'''
import urllib
import json
import cPickle
import sys
import pprint

'''
最后得到一个字典cn，可以这样用
cn[u'山东'][u'菏泽'][u'定陶']=101121005
将cn 保存到pk_file文件
'''
def generateCityCode(pk_file):
    basePath = "http://www.weather.com.cn/data/city3jdata/"
    #得到省级代码列表
    china = urllib.urlopen(basePath+"china.html")
    china = json.loads(china.read())
    '''
        {"10101":"北京","10102":"上海","10103":"天津","10104":"重庆","10105":"黑龙江","10106":"吉林","10107":"辽宁",
        "10108":"内蒙古","10109":"河北","10110":"山西","10111":"陕西","10112":"山东","10113":"新疆","10114":"西藏",
        "10115":"青海","10116":"甘肃","10117":"宁夏","10118":"河南","10119":"江苏","10120":"湖北","10121":"浙江",
        "10122":"安徽","10123":"福建","10124":"江西","10125":"湖南","10126":"贵州","10127":"四川","10128":"广东",
        "10129":"云南","10130":"广西","10131":"海南","10132":"香港","10133":"澳门","10134":"台湾"}
        china是上面这样的一个字典，将它反转过来，即省份作为key，编码作为value
    '''
    cn={}
    for k in china.keys():
        cn[china[k]] = k
    for k in cn.keys():
        province = urllib.urlopen(basePath+"provshi/"+cn[k]+".html")
        province = json.loads(province.read())
        '''
        根据  cn[u'山东']=10112  查询得到市级编码
        {"01":"济南","02":"青岛","03":"淄博","04":"德州","05":"烟台","06":"潍坊","07":"济宁","08":"泰安","09":"临沂",
        "10":"菏泽","11":"滨州","12":"东营","13":"威海","14":"枣庄","15":"日照","16":"莱芜","17":"聊城"}
        下面同样将字典逆转过来,并拼接上省级代码
        '''
        prov = {}
        for sk in province.keys():
            prov[province[sk]] = cn[k]+sk   
        
        for sk in prov.keys():
            city = urllib.urlopen(basePath+"station/"+prov[sk]+".html")
            city = json.loads(city.read())
            '''
            根据prov[u'菏泽']=1011210 等到县级的编码
            {"01":"菏泽","02":"鄄城","03":"郓城","04":"东明","05":"定陶","06":"巨野","07":"曹县","08":"成武","09":"单县"}
            '''
            cities = {}
            for ssk in city.keys():
                cities[city[ssk]] = prov[sk]+ssk
            prov[sk] = cities
        cn[k] = prov
    #将三级字典存储到pk文件
    fp = open(pk_file,'wb')
    cPickle.dump(cn,fp)
    fp.close()
    #return cn
'''
根据<省、市、区/县>进行天气查询
'''
def queryWeather(sheng,shi,xian):
    weatherBasePath = "http://www.weather.com.cn/data/sk/"
    fp = open('citycode.pk','rb')
    china = cPickle.load(fp)
    fp.close()
    code = china[sheng][shi][xian]
    if not code:
        sys.exit(1)
    #四个直辖市，需要将code中的市级代码和区级代码交换位置
    fourCity = [u'北京',u'上海',u'天津',u'重庆']
    if sheng in fourCity:
        cl = len(code)
        adjust_code = code[0:cl-4]+code[cl-2:cl]+code[cl-4:cl-2]
        code = adjust_code
    w = urllib.urlopen(weatherBasePath+code+".html")
    w = json.loads(w.read())
    #w是一个字典，此处的天气状况的解析省去
    pprint.pprint(w)

if __name__=='__main__':
    #generateCityCode('citycode.pk')
    queryWeather(u'山东',u'菏泽',u'定陶')
    queryWeather(u'北京',u'北京',u'海淀')
    queryWeather(u'上海',u'上海',u'浦东')
    queryWeather(u'天津',u'天津',u'塘沽')
    queryWeather(u'重庆',u'重庆',u'江津')
    
