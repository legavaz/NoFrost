# NoFrost

  Lega_dvi:23-12-2020
  скетч создан для работы холодильника по принципам NOFROST
  Репозиторий: https://github.com/legavaz/NoFrost.git
  
  LCD:
  питание:
  gnd - земля
  vcc - 5V
  порты i2c:
  SCL - пин A5
  SDA - пин A4
  
  Датчик температуры (родной):
  питание - 5V (с пина питания)
  снятие аналоговых данных: A0
  

схема:
https://easyeda.com/editor#id=10a0b26cdaf045d7a4ea9bebee2e00f6

принцип работы холодильника NOFROST
1) фаза заморозки
	включение компрессора и вентилятора, работает пока не будет в морозилке -8
	
2) фаза оттаивания
	выключение компрессора и вентилятора, включение тэна, для удаления наледи с радиатора в морозилке
	таймер на работу - около 10-20 минут
	

Тут большинство ответов на вопросы по работе холодильника:
https://vahatehnika.com/holodilnik/ustrojstvo-holodilnika-indezit-dvuhkamernyj.html

https://yandex.ru/video/preview/?text=%D0%BF%D1%80%D0%B8%D0%BD%D1%86%D0%B8%D0%BF+%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B+%D1%85%D0%BE%D0%BB%D0%BE%D0%B4%D0%B8%D0%BB%D1%8C%D0%BD%D0%B8%D0%BA%D0%B0+%D0%BD%D0%BE%D1%83+%D1%84%D1%80%D0%BE%D1%81%D1%82&path=wizard&parent-reqid=1609145631069924-232053183083571860742443-prestable-app-host-sas-web-yp-44&wiz_type=vital&filmId=9732341876902541805&url=http%3A%2F%2Ffrontend.vh.yandex.ru%2Fplayer%2FvT726fuQID0M

Уроки Алекс Гайвер
https://alexgyver.ru/lessons/