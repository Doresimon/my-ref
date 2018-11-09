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

> docker pull hyperledger/fabric-tools:1.1.0

> docker pull hyperledger/fabric-orderer:1.1.0

> docker pull hyperledger/fabric-peer:1.1.0

<!-- > docker pull hyperledger/fabric-javaenv:1.1.0 -->

> docker pull hyperledger/fabric-ccenv:1.1.0

> docker pull hyperledger/fabric-couchdb

> docker pull hyperledger/fabric-ca

> docker pull hyperledger/fabric-kafka

> docker pull hyperledger/fabric-zookeeper


- run sample

> ./byfn.sh -m generate

> ./byfn.sh -m up

> ./byfn.sh -m down

# Chaincode explorer

1. create a *.go file and user chaincode interface from fabric

2. build this file

> go get -u --tags nopkcs11 github.com/hyperledger/fabric/core/chaincode/shim

> go build --tags nopkcs11

3. go to fabric-samples

> cd chaincode-docker-devmode

4. Terminal 1 - Start the network

> docker-compose -f docker-compose-simple.yaml up

5. Terminal 2 - Build & start the chaincode

> docker exec -it chaincode bash

> cd sacc

> go build

> CORE_PEER_ADDRESS=peer:7052 CORE_CHAINCODE_ID_NAME=mycc:0 ./sacc

6. Terminal 3 - Use the chaincode

> docker exec -it cli bash

> peer chaincode install -p chaincodedev/chaincode/sacc -n mycc -v 0

> peer chaincode instantiate -n mycc -v 0 -c '{"Args":["a","10"]}' -C myc

> peer chaincode invoke -n mycc -c '{"Args":["set", "a", "20"]}' -C myc

> peer chaincode query -n mycc -c '{"Args":["query","a"]}' -C myc