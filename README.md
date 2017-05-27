<div class="col-md-8 wrap">

[![Travis-CI][travis-badge]][travis-builds]

[travis-badge]: https://travis-ci.org/lomayka/lab8.svg?branch=master
[travis-builds]: https://travis-ci.org/lomayka/lab8/builds`

## HTTP сервер

#### Мета:

Навчитися створювати простий web-сервер із взаємодією через протокол HTTP. Навчитися оформляти віддалений Git репозиторій із кодом, перевіряти збірки проекту за допомогою безперервної інтеграції та створювати документацію коду проекту.

#### Завдання №1\. Створення web-сервера

Створити TCP-сервер, що слухає запити на підключення TCP клієнтів і взаємодіє з ними за допомогою протоколу **HTTP**. Сервер повинен обробляти лише HTTP **GET** запити і повертати коректно-сформовані HTTP-відповіді. Інтерфейс сервера дозволяє звертатися до нього по HTTP-шляхах:

*   `/` - відправити у відповідь JSON-об'єкт із інформацією про сервер:

        {
            "title": "%SERVER_NAME%", 
            "developer": "%YOUR_NAME_SURNAME%", 
            "time": "%SERVER_TIME%"
        }

*   `/favorites` - JSON-список із об'єктів, що позначають список ваших улюблених тварин. Кожен такий об'єкт має мати декілька полів, серед яких обов'язково має бути числове поле `id` із унікальним для кожного об'єкта значенням.
*   `/favorites?{key}={value}` - JSON-підсписок тих об'єктів зі списку `/favorites`, у яких поле `{key}` має значення `{value}`. Ключ `{key}`, по якому відбувається фільтрація списку, обрати довільно.
*   `/favorites/{id}` - JSON-об'єкт зі списку `/favorites` за ідентифікатором з числовим значенням `{id}`. Якщо об'єкта із таким значенням `id` не було знайдено, повертати у відповідь HTTP статус `404 Not Found`.
*   `/file` - зчитати вміст файлу `data.txt`, який попередньо розмістити у директорії `data/` проекту. Відправити клієнту JSON-об'єкт, що містить у собі інформацію про назву, розмір (у байтах) і текстовий вміст файлу.
*   `/file/data` - у відповідь клієнту відправити JSON-об'єкт із інформацією про найбільшу та найменшу цифру у файлі (файл `data.txt`).

#### Завдання №2\. Створення документації проекту за допомогою Doxygen

##### Коментування коду у форматі Doxygen

Виконати коментування інтерфейсів модулів у форматі `Doxygen` ([приклад](https://github.com/PublicHadyniak/libprogbase/blob/master/include/progbase/list.h)).

Для цього кожен заголовочний файл повинен починатися на коментар виду:

    /** @file
        @brief Some text about this header
    */

Перед кожною визначеною структурою даних має бути коментар:

    /**
        @struct List
        @brief defines a generic List data type
    */

Перед кожною функцією інтерфейсу також розмістити коментар із інформацією про призначення функції, її параметри та результат, що повертається:

    /**
        @brief remove item from list by value
        @param ref - reference to memory from where to read compared value
        @returns true if success removal
    */
    bool List_remove(List * self, void * ref);

##### Генерація HTML-документації утилітою Doxygen

Встановити **Doxygen**:

    sudo apt-get install doxygen graphvis

Перейти у директорію проекта і згенерувати файл із конфігурацією (`Doxyfile`):

    doxygen -g

Задати у `Doxyfile` такі значення для вказаних налаштувань:

    PROJECT_NAME           = "Project Name Here"
    EXTRACT_ALL            = NO
    FILE_PATTERNS          = *.c *.cpp *.h
    RECURSIVE              = YES

Згенерувати документацію командою:

    doxygen Doxyfile

Doxygen створить директорію `docs/` із піддиректоріями `html/` і `latex/`, які міститимуть документацію у різних форматах (не забудьте додати `docs/` у `.gitignore`).

Для перегляду згенерованої документації перейдіть у директорію `html/` і відкрийте файл `index.html` у веб-браузері.

#### Завдання №3\. Безперервна інтеграція (Continuous Integration)

##### CMake

Налаштувати збірку проекта із сервером за допомогою утиліти **cmake** та файлу `CMakeLists.txt` ([приклад](https://github.com/PublicHadyniak/c-project-template/blob/master/CMakeLists.txt)).

##### GitHub репозиторій

Зареєструватись на сайті [Github](https://github.com) та створити віддалений публічний репозиторій, у який надіслати файли проекту. Додатково створити у корені проекту файл `README.md`, у якому у форматі [Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) описати варіант завдання лабораторної роботи та короткий опис модулів проекту.

##### Додаткові скрипти для збірки проекта

Створити у проекті директорію `scripts/` і додати у неї файл `install-libprogbase.sh`:

    #!/bin/sh

    wget -O libprogbase.zip https://github.com/PublicHadyniak/libprogbase/archive/master.zip
    unzip libprogbase.zip -d libprogbase
    cd libprogbase/libprogbase-master ; sudo make install
    cd ../../ ; rm libprogbase/ libprogbase.zip -rf

##### Travis Continuous Integration

Додати у кореневу директорію проекта файл `.travis.yml` із вмістом:

    sudo: required
    language: c
    os:
      - linux
    compiler: 
      - gcc

    before_install:
      - sudo apt-get install libssl-dev
      - sh scripts/install-libprogbase.sh

    script: 
      - cmake . 
      - make .

Зареєструватись на сайті [Travis-CI](https://travis-ci.org) та синхронізувати його із профілем Github. Налаштувати у Travis-CI збірку репозиторія зі сервером. Після кожного `push` комітів у віддалений репозиторій GitHub, Travis-CI збиратиме проект і оновлюватиме статус його збірки (`passing | failing`). Додати у файл `README.md` репозиторія мітку із зображенням статусу збірки та посиланнями на історію збірок ([![Travis-CI](https://travis-ci.org/PublicHadyniak/libprogbase.svg?branch=master)](https://travis-ci.org/PublicHadyniak/libprogbase/builds)) :

    [![Travis-CI][travis-badge]][travis-builds]

    [travis-badge]: https://travis-ci.org/PublicHadyniak/libprogbase.svg?branch=master
    [travis-builds]: https://travis-ci.org/PublicHadyniak/libprogbase/builds

де замінити `PublicHadyniak` на ваш нікнейм на GitHub, а `libprogbase` на назву репозиторія із проектом сервера.

#### Матеріали:

1.  [Лекція. Клієнт-серверна архітектура програм. Сокети, протоколи IP, TCP i UDP.](https://docs.google.com/document/d/1Lm-2s3EyzOd7ynPMKzi53y3kbZ_UwagXfhWCp6dv4sw/edit?usp=sharing)
2.  [Лекція. World Wide Web (WWW). URL. Протокол HTTP](https://docs.google.com/document/d/1aUdlTlbHDYhhdf2gVs1j94FmBrLviKb8QLfFVxqi-0A/edit#heading=h.1ii1x15xikxx)

</div>
