== Задание по параллельному алгоритму имитации отжига ==

Реализуйте параллельный алгоритм имитации отжига.
Решите с его помощью прикладную задачу из области построения расписаний.
Выполните исследование производительности реализованного алгоритма.

=== Прикладная задача ===

Дано N независимых работ, для каждой работы задано время выполнения. Требуется построить расписание выполнения работ без прерываний на M процессорах. На расписании должно достигаться минимальное значение критерия.

Критерий К2: суммарное время ожидания (т.е. сумма, по всем работам, времён завершения работ)

Выбор критерия: на основании остатка от деления на 3 контрольной суммы CRC32 от фамилии и инициалов студента (в формате "ИвановАБ").
Онлайн-расчёт CRC32: https://ru.functions-online.com/crc32.html
* остаток 2: критерий К2

Пояснение к критериям (показаны оси времени процессоров; слева номер процессора; выполняются работы А, Б, В; каждая буква - 1 единица времени выполнения соответствующей работы):

0: АААББ
1: ВВВВВВВВВВВ

Значение критерия К1: 11 (последним освобождается процессор 1)
Значение критерия К2: 19=3+5+11 (сумма времен завершения работ А, Б, В; эти времена считаются не от стартов работ, а от начала расписания)
Значение критерия К3: 6 (разность между временами освобождения процессоров 1 и 0)

=== Требования к реализации алгоритма ИО ===

 - необходимо реализовать параллельный алгоритм ИО с синхронизацией, работающий по описанной в лекции В. Костенко по алгоритмам ИО (далее - просто "лекция") схеме со сбором лучших решений и рассылкой наилучшего
 - параллельный алгоритм ИО должен быть реализован как набор параллельно работающих экземпляров последовательного алгоритма ИО
 - последовательная схема ИО должна быть реализована в виде набора классов С++
   - головной класс: реализует основной цикл ИО в виде, изолированном от конкретных деталей задачи за счёт использования перечисленных далее абстрактных классов; схема работы основного цикла - в соответствии со слайдом "Общая схема" лекции
   - абстрактный класс для представления решения
   - абстрактный класс для операции изменения (мутации) решения
   - абстрактный класс для закона понижения температуры
   - три класса для трёх законов понижения температуры, описанных в лекции
 - алгоритм ИО для конкретной задачи должен быть реализован за счет:
   - реализации класса для представления решения
   - реализации класса для операции мутации решения (содержание операции - на усмотрение студента)
   - выбора закона понижения температуры (одного из трех реализованных в виде классов)
   - "подстановки" этих конкретных классов в головной класс, реализующий схему ИО
 - набор числовых параметров алгоритма (начальная температура и т.п.): в соответствии с содержимым лекции
 - критерий останова (его можно хардкодить): отсутствие улучшения решения в течение K итераций
   - для "внешнего" цикла параллельного ИО: К_внеш=10
   - для "внутреннего" последовательного ИО: К_внутр=100
   - улучшение решения - это нахождение нового решения с меньшим значением минимизируемого критерия, чем у НАИЛУЧШЕГО ранее найденного решения 
 - не забывайте переинициализировать датчик случайных чисел, иначе алгоритм станет детерминированным!

Требования к параллельной реализации:
Вариант 1: многопоточная реализация с обменом данными через разделяемую память
Вариант 2: многопроцессная реализация с обменом данными через файл или сокет

Число потоков/процессов Nproc - числовой параметр реализации.

Детали реализации обмена данными - на усмотрение студента. Можно использовать библиотечные реализации.

Выбор варианта параллельной реализации: на основании значения контрольной суммы CRC32 от фамилии и инициалов студента (в формате "ИвановАБ").
Если контрольная сумма нечётная, то вариант 1. Если чётная, то вариант 2.

=== Требования к исследованию ===

Написать генератор входных данных (описание набора работ). Формат данных - XML или CSV.
Параметры генератора: число процессоров, число работ, диапазон длительностей работ.

Экспериментально определите, при каких количествах процессоров и работ (N и M) последовательный (Nproc=1) алгоритм ИО работает больше 1 минуты хотя бы с одним из законов понижения температуры. С каким из законов понижения температуры на таких алгоритм работает дольше всего на таких "тяжёлых" входных данных? Находит ли он при этом лучшие решения, чем при других законах понижения температуры?

В дальнейших экспериментах используйте один закон понижения температуры. Используйте данные, на которых последовательный ИО работает больше 1 минуты.

Экспериментально определите (постарайтесь найти компьютер с 4 процессорными ядрами):
* какое значение Nproc следует задавать, чтобы параллельная реализация находила решение быстрее, чем последовательная. Или она будет работать точнее (находить лучшее решение), но не быстрее?
* повышение Nproc выше какого значения не дает значительного (более чем на 10%) прироста по скорости.
  * под приростом по скорости понимается сокращение длительности работы алгоритма (от старта до завершения)

=== Рекомендации по отладке алгоритма ИО ===

Отлаживайте с критериями-отрицаниями, тогда нахождение оптимального решения проверяется просто:
отрицание К1 => строится самое длинное расписание (все работы на одном процессоре; если алгоритм хорошо рандомизирован, то от прогона к прогону процессор будет разным, а работы будут расположены в разном порядке)
отрицание К3 => то же, что для отрицания К1
отрицание К2 => то же, что для отрицания К1, плюс работы выстраиваются от самой длинной к самой короткой по убыванию длительности