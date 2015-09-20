#!/usr/bin/python
#_*_coding:utf-8_*_

import os,time,sys

##############################
#########新手慎用#############
##############################

flyer = ["mysql","-ukitty","-p123456","-h192.168.2.24","mobile_kitty"]
databases = [flyer]


tempsql = os.getcwd() + os.sep + "temp.sql"

def mktempsql():
	if not os.path.exists(tempsql):
		os.mknod(tempsql)

def excSql():
	for database in databases:
		sql = " ".join(database) + " < " + tempsql
		os.system(sql)

def copydata(text):
	mktempsql()
	curdir = os.getcwd() 
	text = curdir + os.sep + text
	if not os.path.exists(text):
		os.mknod(text)
	try:
		file_object = open(text)
		file_tmp = open(tempsql,"w")
		for line in file_object:
			if (not line.startswith("--")) and (not len(line) <= 0) and (not line.startswith("#")):
				try:
					file_tmp.write(line)
				except:
					print "写入数据失败"
	except:
		pass
	finally:
		file_object.close()
		file_tmp.close()
		excSql()
		os.remove(tempsql)

def update():
	try:
		copydata("update.sql")
	except:
		print "执行数据库失败"

def install():
	try:
		copydata("install.sql")
	except:
		print "安装数据库失败"

def main():
	reload(sys)
	sys.setdefaultencoding("utf-8")
	if len(sys.argv) < 2:
		usage()
		sys.exit()
	if sys.argv[1] == "update":
		update()
	elif sys.argv[1] == "install":
		install()
	else:
		print "非法的操作"

def usage():
	print "usage:\n\tupdate\t修改数据库表 当前目录需要update.sql文件\n\tinstall\t安装数据库 当前目录需要install.sql文件"

if __name__ == "__main__":
	main()
