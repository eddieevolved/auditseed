Quick Docker image for seedd
---------------------------

Build docker image:
   
    docker/build.sh

Push docker image:

    docker/push.sh

Pull seedcore/seed:latest from docker hub  at [seed-dockerhub](https://hub.docker.com/r/seedcore/seed/)

    sudo docker pull seedcore/seed
    
Run docker image

    sudo docker run seedcore/seed

Build docker for seedd
----------
A Docker configuration with seedd node by default.

    sudo apt install apt-transport-https ca-certificates curl software-properties-common; curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -; sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"; sudo apt-get update; sudo apt install docker-ce   
---------------------------------------------------        
    
    mkdir seed-mounted-data
    docker run --name seed -d \
     --env 'SEED_RPCUSER=rpciser' \
     --env 'SEED_RPCPASSWORD=rpcpassword' \
     --env 'SEED_TXINDEX=1' \
     --volume ~/seed-mounted-data:~/.seed \
     -p 42421:42421 \
     --publish 42421:42421 \
     seedcore/seed
----------------------------------------------------
Logs

    docker logs -f seed

----------------------------------------------------

## Configuration

Set your `seed.conf` file can be placed in the `seed-mounted data` dir.
Otherwise, a default `seed.conf` file will be automatically generated based
on environment variables passed to the container:

| name | default |
| ---- | ------- |
| BTC_RPCUSER | rpcuser |
| BTC_RPCPASSWORD | rpcpassword |
| BTC_RPCPORT | 42421 |
| BTC_RPCALLOWIP | ::/0 |
| BTC_RPCCLIENTTIMEOUT | 30 |
| BTC_DISABLEWALLET | 1 |
| BTC_TXINDEX | 0 |
| BTC_TESTNET | 0 |
| BTC_DBCACHE | 0 |
| BTC_ZMQPUBHASHTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBHASHBLOCK | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWBLOCK | tcp://0.0.0.0:28333 |


## Daemonizing

If you're daemonizing is to use Docker's 
[Daemonizing](https://docs.docker.com/config/containers/start-containers-automatically/#use-a-restart-policy),
but if you're insistent on using systemd, you could do something like

```
$ cat /etc/systemd/system/seedd.service

# seedd.service #######################################################################
[Unit]
Description=Seed
After=docker.service
Requires=docker.service

[Service]
ExecStartPre=-/usr/bin/docker kill seed
ExecStartPre=-/usr/bin/docker rm seed
ExecStartPre=/usr/bin/docker pull seedcore/seed
ExecStart=/usr/bin/docker run \
    --name seed \
    -p 42421:42421 \
    -p 42421:42421 \
    -v /data/seedd:/root/.seed \
    seedcore/seed
ExecStop=/usr/bin/docker stop seed
```
