## Компиляция утилиты Lexicon в Ubuntu

Для успешной компиляции необходимо иметь установленные dev-версии библиотек ncurses и sqlite.
Их можно установить такими командами в консоли:

sudo apt-get install libncurses-dev  
sudo apt-get install sqlite3 libsqlite3-dev  

Также нужно создать временный каталог /tmp/lexicon.

После этого надо перейти в каталог src/demo/ai/solarix/lexicon/ и запустить ./build.sh

После окончания сборки появится исполнимый файл lexicon


