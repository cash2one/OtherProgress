#/bin/bash

cond=$(ps -u $(basename $HOME) | grep -c Server)
redis=$(ps -u $(basename $HOME) | grep -c redis-server)

ulimit -c unlimited

start()
{
	rm $HOME/log/*

#	while [ $cond -gt 0 -o $redis -gt 0 ];
#	do
		stop
#	done

	echo "start ./redis-server"
#	redis-server ~/redis.conf
	sleep 1
	echo "start ./superserver/superserver"
	./superserver/superserver -d
	sleep 1
	echo "start ./recordserver/recordserver"
	./recordserver/recordserver -d
	sleep 1
	echo "start ./sessionserver/sessionserver"
	./sessionserver/sessionserver -d
	sleep 1
	echo "start ./sceneserver/sceneServer"
	./sceneserver/sceneserver -f /home/flyer/newWorkPlace/tempKitty/log/sceneserver1.log -d
	sleep 1
	./sceneserver/sceneserver -f /home/flyer/newWorkPlace/tempKitty/log/sceneserver2.log -d
	echo "start ./gateserver/gateserver"
	./gateserver/gateserver -f /home/flyer/newWorkPlace/tempKitty/log/gateserver1.log -d
	sleep 1
	./gateserver/gateserver -f /home/flyer/newWorkPlace/tempKitty/log/gateserver2.log -d
	sleep 2

	redis=$(ps -u $(basename $HOME) | grep redis-server)
	echo "$redis"
	cond=$(ps -u $(basename $HOME) | grep server | grep -v redis-server)
	echo "$cond"
}

stop()
{
	echo "stop ./redis-server"
#	pkill redis-server
	sleep 1
	echo "stop ./superserver/superserver"
	pkill superserver
	sleep 1
	echo "stop ./recordserver/recordserver"
	pkill recordserver 
	sleep 1
	echo "stop ./sessionserver/sessionserver"
	pkill sessionserver
	sleep 1
	echo "stop ./sceneserver/sceneserver"
	pkill sceneserver
	sleep 1
	echo "stop ./gateserver/gateserver"
	pkill gateserver
##
##	while [ $cond -gt 0 -o $redis -gt 0 ];
##	do
##		cond=$(ps -u $(basename $HOME) | grep -c server)
##		redis=$(ps -u $(basename $HOME) | grep -c redis-server)
##		echo "ServerNum:$cond  RedisNum:$redis"
##		sleep 1
##	done
}

case $1 in
	start)
	start
	;;
	stop)
	stop
	;;
	*)
	stop
	start
	;;
esac
