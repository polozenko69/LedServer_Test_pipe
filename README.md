# Тестовый проект LedServer_Test_pipe

Тестовое задание по созданию клиет-серверного приложения  
управления светодиодом.

* Операционная система: Linux  
* Сервер реализация: c++  
* Клиент реализация: скрипт BASH  
* Взаимодействие: именованные каналы  


## Состав:

**bin**	- каталог для сборки исполняемого файла сервера  
**client**	- каталог клиентских скриптов  
**src**	- каталог исходных текстов сервера  

*Makefile*	- файл сборки исполняемого файла сервера  

*README.md*	- этот файл  


## Сборка и установка.

В каталоге проекта выполнить:  

*make*  
*sudo make install*


## Использование.

Запуск сервера:  
*serverLed start*

останов:  
*serverLed stop*

доступные команды:  
*serverLed {start|stop|restart|status}*


### Если необходимо контролировать работу сервера,

то запуск осуществить в консоле командой:  
*LedServer*

останов: *Ctrl-C*


## Запуск клиента:

*clientLed*


Работоспособность проверялась Debian 7, Kubuntu 16.04