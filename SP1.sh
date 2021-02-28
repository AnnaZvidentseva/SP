#!/bin/bash

clear

echo "Программа поиска репозитория"
echo "Программа выводит список репозиториев, ищет репозиторий по имени и выводит информацию о нем, если репозиторий не найден, создает новый"
echo "Разработчик: Звиденцева Анна."

repo=""
YN=""
link=""

while true
do
	echo ""
	echo "Список репозиториев"
	awk '{print $NF}' etc/apk/repositories
	echo ""
	echo "Введите название репозитория"
	read repo

	if ( grep -q $repo etc/apk/repositories )
	then
		grep $repo etc/apk/repositories
	else
		echo "Введите ссылку на репозиторий"
		read link
		echo "$link" >> etc/apk/repositories
		apk update
	fi

	while true
	do
		echo "Завершить работу программы?"
		echo "(y/n)"
		read YN
		case "$YN" in
			"Y" | "YES" | "Yes" | "y" | "yes" | "ДА" | "Д" | "Да" | "д" | "да") echo "До свидания!"; exit $?;;
			"N" | "NO" | "No" | "n" | "no" | "Н" | "НЕТ" | "Нет" | "н" | "нет") echo ""; break;;
			* ) echo "Ошибка! Вы должны ввести (д/н) или (y/n)" >/dev/stderr;;
		esac
	done
done
