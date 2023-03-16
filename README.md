# библиотека для построения графиков функций одной переменной в декартовых координатах
Было разработано ядро приложения, распознающее пользовательский ввод и подающее на вывод значение функции в конкретной заданной точке.
На ядро наращен GUI. Также есть реализация и с примитивным консольным интерфейсом: https://github.com/MupLever/Draw_graph_in_console
К сожалению, у проекта есть недостатки, а именно проблема обработки неправильного ввода.
# Чтобы развернуть приложение, надо:
1.	Установите qmake;
2.	Откройте терминал и склонируйте репозиторий к себе на компьютер командой: git clone git@github.com:MupLever/qt_graph_builder.git;
3.	Откройте папку «qt_graph_builder» в терминале;
4.	Выполните следующую команду: qmake cproject.pro;
5.	Выполните следующую команду: make -j1;
6.	Для запуска выполните следующую команду: ./cproject.

# Ссылка на полную документацию: 
https://drive.google.com/drive/folders/1sAFuZIrvI6-_FSewCmhvArVgLI-bii2p?usp=sharing
