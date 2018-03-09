# GraphicApplication 
===================
	
![выделение нескольких объектов](/images/1.jpg)
![рендер линий](/images/2.jpg)

Приложение для просмотра\открытия .obj моделей
Выделения несколькх объектов 

ESRI shape файлов 
[вики](https://ru.wikipedia.org/wiki/Shapefile)


Достоинства 
--------

* Кроссплатформенное приложение, запустися в windows linux (в linux нужно установить драйвера видео карты lib-mesa)
* перемещения\поворот камеры камеры 
* Современный OpenGL для моделей(шейдеры, никаких glbegin(...) loadIndentity() и т п )  и 2% цп(не предел), 14 мб оперативной памяти
* Выделение
* imgui - легкая Си библиотека для пользовательского интерфейса
* никаких кнопок закрыть свернуть развернуть- приложение можно "таскать" за верхнюю часть и развернуть на половину справа слева экрана и полностью сверху(сделано для экономии места на экране)

Горячие клавиши
---------
wasd - перемещение камеры
1 - создать плоский объект с текстурой
3 - рендер линий
4 - обычный рендер
f - создать 3д модель куба (TODO: нарушена загрузка индексов вершин, поэтому оображение некорректное)
левая кнопка мыши- выделение (зажать для рамки)
средняя кнопка мыши- поворот камеры
esc - выход из приложения

Компилирование windows
---------
cd build
cmake ..
mingw32-make 

Компилирование linux
---------
cd build
cmake ..
make 
sudo apt-get install doxygen
в cmakeLists.txt предусмотрена сборка документации (по умолчанию отключена, флаг BUILD_DOC)
соберется в папку documentation проекта

Зависимости
---------
Использованы библиотеки
[glew](http://glew.sourceforge.net/) 
[glm](https://glm.g-truc.net/0.9.8/index.html) 
[SDL2](https://www.libsdl.org/index.php) 
[SDL2_net](https://www.libsdl.org/projects/SDL_net) 
[imgui](https://github.com/recastnavigation/recastnavigation/blob/master/RecastDemo/Include/imgui.h)
[stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h)
Все они уже включены в libs/ проекта , Cmake линкует все статически- на выходе один исполняемый файл 


Запуск
-------
exe и dll файлы лежат в build/release
рядом обязатеьно должны быть файлы ресурсов (шрифт модель и текстуры)

Недостатки 
-------
* obj индексы 3d моделей некорректны
* Пока рендерит замкнутые линии shape файлов, нет текста, точек
* Грязьненький код в 100>строк в одной функции (код полгода без обновлений)

Использование / Contributing 
--------------------
[learnopengl -camera]( https://learnopengl.com/Getting-started/Camera) 
[wikibooks - Object selection](https://en.wikibooks.org/wiki/OpenGL_Programming/Object_selection) 

 
All my source code is licensed under BSD. You can use it without any restrictions, just give a reference to this repo.
Мой код можно использовать как угодно с ссылкой на этот репозиторий.