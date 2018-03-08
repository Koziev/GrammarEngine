# -*- coding: utf-8 -*- 

from __future__ import print_function
import requests
import json
import codecs

def urlencode(u):
 return str.join( '', [ '%{0:x}'.format( ord(c) ) for c in u.encode('utf-8') ] )

# REST-сервис парсера запущен на этом хосте
base_url = 'http://127.0.0.1:10973/tag1?'

# Читаем тестовые предложения, посылаем их на частеречный
# разбор сервису парсинга.
with codecs.open('1.txt', 'r', 'utf-8') as rdr:
    for line in rdr:
        sent = line.strip()
        print(u'Sentence={}'.format(sent))
        url = base_url + 'sent=' + urlencode(sent)
        response = requests.get(url)
        print(u'status={0}'.format(response.status_code))
        print(u'RESPONSE: ', response.json())
        print('\n')
