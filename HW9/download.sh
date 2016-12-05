#!/bin/sh

d=`date +%Y_%m_%d_%H_%M_%S`
fn="nyse_${d}.html"
wget -O $fn http://online.wsj.com/mdc/public/page/2_3021-activnyse-actives.html
java -jar tagsoup-1.2.jar --files $fn

python parse.py "nyse_${d}.xhtml"
