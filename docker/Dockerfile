#FROM debian:stretch
FROM ubuntu:18.04
LABEL maintainer="The Seedcore Developers <devstar11@seedcore.io>"
LABEL description="Dockerised Seedcore, built from Travis"

RUN apt-get update && apt-get install -y software-properties-common unzip
RUN apt-get install -y wget

RUN wget https://github.com/SEED-Core/seed/releases/download/v5.2.3/seed-qt-linux-18.zip
RUN unzip seed-qt-linux-18.zip
RUN cp seedd /usr/local/bin

VOLUME ["/opt/seed"]

EXPOSE 42421
EXPOSE 42421
EXPOSE 9777
EXPOSE 9777

CMD ["seedd", "--conf=/opt/seed/seed.conf", "--printtoconsole"]