#/bin/bash

cond=$(ps -u $(basename $HOME) | grep -c Server)

ulimit -c unlimited

start()
{
	while [ $cond -gt 0 ];
	do
		stop
	done

    removelog
	sleep 1
	echo "start ./superserver/superserver"
	./superserver/superserver -d
	sleep 1
	echo "start ./recordserver/recordserver"
	./recordserver/recordserver -d
    sleep 1
	echo "start ./recordserver/recordserver"
	./recordserver/recordserver -d
	sleep 1
	echo "start ./sceneserver/sceneServer"
    ./sceneserver/sceneserver -d 
	sleep 1
	./sceneserver/sceneserver -d 
	echo "start ./gateserver/gateserver"
	./gateserver/gateserver -d 
	sleep 1
	./gateserver/gateserver -d 
	sleep 2

	cond=$(ps -u $(basename $HOME) | grep server)
	echo "$cond"
}

function removelog()
{
    if [ -d log ]
    then
        rm -rf log/superserver*.*
        rm -rf log/billgatewayserver*.*
        rm -rf log/gatewayserver*.*
        rm -rf log/recordserver*.*
        rm -rf log/sceneserver*.*
        rm -rf log/billsuperserver*.*
        rm -rf log/recharge_superserver*.*
    else
        mkdir log
    fi
}

stop()
{
	sleep 1
	echo "stop ./superserver/superserver"
	pkill superserver
	sleep 1
	echo "stop ./recordserver/recordserver"
	pkill recordserver 
	sleep 1
	sleep 1
	echo "stop ./sceneserver/sceneserver"
	pkill sceneserver
	sleep 1
	echo "stop ./gateserver/gateserver"
	pkill gateserver

	while [ $cond -gt 0 ]
	do
		cond=$(ps -u $(basename $HOME) | grep -c server)
		echo "ServerNum:$cond"
		sleep 1
	done
}

function stopflserver()
{
    sleep 1
    echo "stop ./flserver/flserver"
    pkill flserver
    
    local cond=$(ps -u $(basename $HOME) | grep -c flserver)
    
    while [ $cond -gt 0 ]
	do
		cond=$(ps -u $(basename $HOME) | grep -c flserver)
		echo "flserverNum:$cond"
		sleep 1
	done
    rm -rf log
}


case $1 in
	start)
	start
	;;
	stop)
	stop
	;;
    debug)
    stopflserver
    stop
    sleep 1
    mkdir log
	echo "start ./flserver/flserver"
	./flserver/flserver -d
    start
    ;;
	*)
	stop
	start
	;;
esac
