# Практикум, 7 семестр
# Задание 1, Звонов Андрей, 421

---
Описание задания --- в task.md
# Що да как
Писалось и запускалось под Ubuntu 20.04
#### Установка:
1. Подготовка:
```
sudo apt-get install libreoffice
sudo apt-get install libreoffice-dev*
sh /usr/lib/libreoffice/sdk/setsdkenv_unix.sh
```
На последнем шаге желательно выбрать `Auto Deployment = YES`, чтобы оно всё само установилось
2. Установка
```
git clone https://github.com/zvonand/prak7.git
cd prak7
make -B
```
3. Вы прекрасны!!!

#### Использованные материалы
* https://niocs.github.io/LOBook/extensions/
