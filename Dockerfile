FROM debian:latest
MAINTAINER MATHIEU mathieu.bordere@sioux.eu

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install procps libstorable-perl wget perl libnet-ssleay-perl openssl libauthen-pam-perl libpam-runtime libio-pty-perl python apt-utils
RUN rm /etc/apt/apt.conf.d/docker-gzip-indexes
RUN apt-get purge apt-show-versions
RUN rm /var/lib/apt/lists/*lz4
RUN apt-get -o Acquire::GzipIndexes=false update
RUN apt-get -y install apt-show-versions
RUN wget https://sourceforge.net/projects/webadmin/files/webmin/1.910/webmin_1.910_all.deb
RUN dpkg --install webmin_1.910_all.deb
