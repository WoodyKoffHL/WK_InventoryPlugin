# WK_InventoryPlugin
Документация.

      1.Установка и настройка
      
      2.Создание предметов, основные события
      
      3.Класс WK_Item
      
      4.Создание базы предметов
      
      5.Создание pick up actor
      
      6.Настройка слотов инвентаря
      
      7.Настройка Карманов
      
      8.Настройка Экипировки
      
      9.Настройка слотов оружия  
      
      10.Описание CPP Компонента

      11.Интерфейс


**<h2>1.Установка и настройка</h2>**

Создаем необходимые Блюпринты под наши компоненты, итемы и т.п. Начинаем с Компонента Inventory component

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/729e2e1a-528a-4c81-a186-8e1e04f31fe5)

Добавляем нашему персонажу данный компонент. В деталях компонента необходимо произвести первоначальные настройки, где 1, 2, 3 - размеры слотов инвентаря. А Именно основного инвентаря, быстрых слотов и слотов экипировки. 

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/fa8f5cf5-165f-4de0-9a87-c7c07615102c)

Слоты 5, 6, 7 - Стартовые слоты. При старте - Основные слоты генерируются как пустые, после чего в них добавляется всё из старотовых. Создано для сохранений игровых сессий, защищенного старта игры. В Общем - так надо.

Проверить сгенерировались слоты можно простыми махинациями с циклами и принт стрингами 

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/a806c7c1-17c6-4dc3-8211-4c70686eea28)

Для взаимодействий нам понадобятся так же следующие блюпринт объекты:

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/8be84a7f-8717-4ec6-9717-3184f2bcca43)




**1: BP_Item** - Дочерний класс от WK_Item. В нем хранятся события, которые происходят при использовании предмета, изменения его свойств и т.д. Под каждый Итем - свой БП, или обобщенный. Можно создавать дочерние классы и размещать по папкам.

**2: BP_PickUp** - Дочерний класс от WK_PickUpActor - Это объект, который будет визуализировна на карте. Его можно подобрать, создать при выкидывании предмета и т.д.

**3: DB_Items** - Это Data Asset с нашей структурой Items. Внутри хранится вся информация о существующих предметах. Некая база данных, с которой мы будем постоянно работать.


Для объектов взяаимодействия (ПикАп и Персонажу) Добавляем интерфейс WK Interface. Подробнее об интерфейсе в п.11

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/3cc3327d-f03a-46a8-9400-b8ba31e4e31c)




**<h2>3.Класс WK_Item</h2>**

Класс отвечает за использование предметов. Переменная can use - определяет - можно ли использовать этот предмет.

Call Using Item - Вызов кода испольования.

Check Can Using Event - Код для проверки использования. Необходимо задавать значение переменной can Use.

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/cd909a02-997e-40ad-96ea-94415c22e8fb)


**<h2>10. Описание С++ Inventory Component</h2>**

**<h3>Функции для Blueprints</h3>**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/5c641135-8328-4152-b8b1-2f1ad2143ba8)

**Add Item** - Добавляет предмет. В зависимости от настроек - стакает предметы. Возвращает boolean - был ли добавлен предмет или нет.

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/bb0620a1-0066-49c8-8980-3dabe2d974c4)

**Swap Items** - меняет местами 2 слота. Принимает 2 индекса

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/6eb43427-d69e-46a1-8de1-5665a6bc6bec)

**Get Item Info** - Принимает аргумент - ID предмета из базы (Не индекс). На выходе выдают структуру из базы данных. Является Pure функцией.

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/e3e80076-c87c-41a9-9901-eb5f142b6325)

**Use Item At Index** - Использовать предмет в слоте. Входящие парметры: Тип слотов (Инвентарь, быстрые слоты, Экипированные слоты), индекс и количество. Используется только с Useble и UseItem. То есть предмет Может имет тип - for Using, но не Useble, тоесть  использоваться при других обстоятельствах, например для квестов, Крафте и т.п.

**Set Near Item** - Устанавливает Pick Up Actor - как ближайший. Если Activate - false - сбрасывает до пустой ссылке. Таким образом можно настроить добавление предмета в инвентарь по кнопке действия.

**Use ItemBy ID** - Позволяет использовать предмет по его ID. Полезно при каких то кастомных предметах, у которых может быть несколько эффектов от итемов. Например - Использовать несколько зелий, Бафов и т.п. 

**Fast Use Item From Pick Up** - Быстрое использование предмета из Pick Up Actor. Идёт проверка класса итема, если можно использовать, то пик ап эктор уничтожается и предмет используется. 

Использование других типов:

В разработке

**<h2>11. Интерфейс С++ WK Interface</h2>**

**<h3>Функции для Blueprints</h3>**

**Set Near Item**  Вызовет event у персонажа, если интерфейс подключен. 

**В Объекте ПикАп - Идет проверка Типа предмета, и у соприкосаемого персонажа (Local Actor) - идёт поптка вызова функции интерфейса**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/6bc2640e-4692-47f5-9b48-bb7384b53ebd)

**В вызове функции интерфейса (event set near item) мы можем кастомизировать процесс установки ПикАп объекта или вызвать стандартную функцию инвентаря, как на скриншоте:**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/748e4987-ca8e-449a-9847-f9ac7dbb11c8)

**Fast Use Item**  Вызовет event у персонажа, если интерфейс подключен. Позволяет быстро использовать Итем, не добавляя в инвентарь.

**Так же идёт проверка на тип (Для примера) - После чего идёт сообщение по интерфейсу.**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/c670397c-ebcc-4ce0-8e8f-141eca1eec16)

**У персонажа вызывается Event  - Который можно кастомизировать или вызвать стандартную функцию Инвентаря - Fast Use item from Pick Up**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/9764d26d-b609-4263-b7e1-1e56a333af75)

**Ровно по тому же принципу вызывается Event - Call Add Item**

![image](https://github.com/WoodyKoffHL/WK_InventoryPlugin/assets/116869579/b5d65b6f-e4eb-4ee9-b6c3-87d113f84097)








**<h2>Описание Blueprint Ivents в Inventory Component</h2>**


