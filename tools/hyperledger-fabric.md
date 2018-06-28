# Hyperledger - Fabric

# Ubuntu 18.04

> sudo apt install docker.io

- ## [Hyperledger/Fabric CN Docs](https://hyperledgercn.github.io/hyperledgerDocs/blockchain_zh)



- give user access to docker:

> sudo usermod -aG docker $USER

> sudo setfacl -m user:$USER:rw /var/run/docker.sock

> sudo groupadd docker

> sudo gpasswd -a ${USER} docker

> sudo service docker restart

> newgrp - docker


- change registry mirror

> sudo echo "DOCKER_OPTS=\"--registry-mirror=http://hub-mirror.c.163.com"" >> /etc/default/docker

> sudo echo "DOCKER_OPTS=\"--registry-mirror=https://docker.mirrors.ustc.edu.cn\"" >> /etc/default/docker

> sudo service docker restart

or

create file:  daemon.json
```
{
    "registry-mirrors": ["http://hub-mirror.c.163.com", "https://mirror.gcr.io"]
}
```
> sudo cp daemon.json /etc/docker/

> sudo service docker restart


- add images

> docker pull hyperledger/fabric-couchdb

> docker pull hyperledger/fabric-ca

> docker pull hyperledger/fabric-kafka

> docker pull hyperledger/fabric-zookeeper


- run sample

> ./byfn.sh -m generate

> ./byfn.sh -m up

> ./byfn.sh -m down
