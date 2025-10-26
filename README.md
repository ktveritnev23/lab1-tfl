# Лабораторная работа №1 (Тверитнев Михаил, ИУ9-51Б, вариант 25).

## 0. Исходная система T.

$$
T =
\left\lbrace
  \begin{array}{lr}
    \text{bbb} \to \text{bab} \\
    \text{abab} \to \text{bab} \\
    \text{abba} \to \text{aba} \\
    \text{babb} \to \text{abb} \\
    \text{bbab} \to \text{bab} \\
    \text{aaaaa} \to \text{a} \\
    \text{aaaba} \to \text{bba} \\
    \text{aaaabb} \to \text{bb} \\
    \text{abb} \to \text{abaaaa}\\
    \text{abaaab} \to \text{ab} \\
    \text{baaaab} \to \text{bab} \\
    \text{baaabb} \to \varepsilon \\
    \text{bbaaaa} \to \text{bb} \\
    \text{bbaaab} \to \text{aaaab} \\
    \text{baabaab} \to \text{baaab} \\
    \text{babaaba} \to \text{bab} \\
    \text{babaabb} \to \text{babaaa},
\end{array}
\right. 
\Sigma = \lbrace\text{a}, \text{b}\rbrace.
$$


## 1. Завершимость - система не завершима.

Возможные изменения длин при однократном применении правила: $\Delta{|w|} (l_i \to r_i) \in\lbrace -6; -4; -3; -2; -1; 0; +3\rbrace$.

Для цикла необходимо, чтобы длина в начале и конце цикла не отличалась.

Попробуем построить цикл на основе $\text{abb} \to \text{abaaaa}$. Тогда нужно либо три правила, укорачивающих слово на 1, либо одно правило, укорачивающее слово на 2 и одно, уменьшающее $|w|$ на 1, или же одно правило, сокращающее длину на 3.

Вариант с сокращением длины на 3 нерабочий: $\text{abbb} \to \text{abaaaab} \to \text{abab}$. Для продолжения переписывания нужно поглотить букву $b$ из правого контекста.

Если сначала сократить на 2, затем на 1: $\text{aaabb} \to \text{aaabaaaa} \to \text{bbaaaa}$. Подходящих правил, уменьшающих длину на 1, не существует. Чтобы не сокращать длину, нужно поглотить три буквы $a$ из левого контекста. Очевидно, такой цикл бесконечным быть не может, поскольку $\text{bb}$ смещается к началу слова.

Сокращение сначала на 1, затем на 2 символа: $\text{abbbab} \to_{R9} \text{abaaaabab} \to_{R2} \text{abaaabab} \to_{R7} \text{abbbab}$. Этот цикл можно встроить в любой контекст и получить бесконечную цепочку переписываний.

Чтобы избавиться от цикла, изменим направление переписывания $\text{abb} \to \text{abaaaa}$. 

Докажем, что полученная система уже завершима.

Введём лексикографический кортеж на строках:

$$
Q(w) = (|w|, E(w), R(w)) \in \mathbb{N}^3,
$$

где:
- $E(w) = \sum_{i} M(w_i)\in \mathbb{N}$, $M(a) = 1$, $M(b) = 2$,
- $R(w) = \sum_{i : w_i = b}2^i - \sum_{i : w_i = a}2^i + 2^{|w|}.$

Он строго уменьшается при применении любого правила переписывания (если не уменьшается вес $E(w)$, уменьшается длина). Третий элемент понадобится дальше, при пополнении; для простого доказательства завершимости хватит и пары $(|w|, E(w))$.

Таким образом, поскольку $\langle\mathbb{N}^3, \lt\rangle$ является фундированным множеством, бесконечных цепочек переписываний нет и система завершима.

$$
T_{term} =
\left\lbrace
  \begin{array}{lr}
    \text{bbb} \to \text{bab} \\
    \text{abab} \to \text{bab} \\
    \text{abba} \to \text{aba} \\
    \text{babb} \to \text{abb} \\
    \text{bbab} \to \text{bab} \\
    \text{aaaaa} \to \text{a} \\
    \text{aaaba} \to \text{bba} \\
    \text{aaaabb} \to \text{bb} \\
    \text{abaaaa} \to \text{abb}\\
    \text{abaaab} \to \text{ab} \\
    \text{baaaab} \to \text{bab} \\
    \text{baaabb} \to \varepsilon \\
    \text{bbaaaa} \to \text{bb} \\
    \text{bbaaab} \to \text{aaaab} \\
    \text{baabaab} \to \text{baaab} \\
    \text{babaaba} \to \text{bab} \\
    \text{babaabb} \to \text{babaaa}
\end{array}
\right. 
$$

## 2. Число классов эквивалентности по НФ - конечно.

Множество нормальных форм конечно.

$\varepsilon$ - НФ.

Правило $\text{aaaaa} \to \text{a}$ даёт четыре НФ: $\{\text{a}, \text{aa}, \text{aaa}, \text{aaaa}\}$, в которые сходятся любые строки вида $\text{a}^n$.

Применим различные префиксы из НФ к $\{\text{a}, \text{aa}, \text{aaa}, \text{aaaa}\}$:

$\text{b} \to \{\text{ba}, \text{baa}, \text{baaa}, \text{baaaa}\}$;

$\text{bb} \to \{\text{bba}, \text{bbaa}, \text{bbaaa}\}$;

$\text{ab} \to \{\text{aba}, \text{abaa}, \text{abaaa}, \text{abaaaa}\}$;

$\text{aab} \to \{\text{aaba}, \text{aabaa}, \text{aabaaa}, \text{aabaaaa}\}$;

$\text{bab} \to \{\text{baba}, \text{babaa}, \text{babaaa}, \text{babaaaa}\}$;

$\text{baab} \to \{\text{baaba}, \text{baabaa}, \text{baabaaa}, \text{baabaaaa}\}$;

$\text{bbaab} \to \{\text{bbaaba}, \text{bbaabaa}, \text{bbaabaaa}, \text{bbaabaaaa}\}$;

$\text{abaab} \to \{\text{abaaba}, \text{abaabaa}, \text{abaabaaa}, \text{abaabaaaa}\}$;

$\text{aabaab} \to \{\text{aabaaba}, \text{aabaabaa}, \text{aabaabaaa}, \text{aabaabaaaa}\}$;

Применим различные суффиксы из НФ к $\{\text{a}, \text{aa}, \text{aaa}, \text{aaaa}\}$:

$\text{b} \to \{\text{aaab}, \text{aaaab}\}$.

Заметим, что $\text{bb}$ в НФ может быть 0 или 1, причём только в начале слова ($\text{babb} \to \text{abb}$, $\text{aaaabb} \to \text{bb}$ сдвигают $\text{bb}$ влево, $\text{bbb} \to \text{bab}$ убирает стоящие подряд $\text{bb}$). Также заметим, что префикс и инфикс НФ, состоящий из букв $\text{a}$, не может быть длиннеe 2 (c исключениями $\text{aaa}, \text{aaaa},  \text{baaab}$).

Остался $\text{babaab}$. Всего **53** нормальные формы.

Убедимся в конечности множества НФ, построив дерево нормальных форм:

![NF tree](graphs/NF%20tree.png "Дерево НФ")

## 3. Локальная конфлюэнтность.

Пример неоднозначно сходящейся критической пары:

$$
u = \text{babb}; 
$$
$$
u \to v = \text{abb} \quad (\text{babb} \to \text{abb}); 
$$
$$
u \to w = \text{babaaaa} \quad (\text{abb} \to \text{abaaaa}); 
$$
$$
v \to v' = \text{abaaaa} \quad (\text{abb} \to \text{abaaaa}).
$$

$v'$ и $w$ являются нормальными формами и не равны $\Rightarrow$ локальная конфлюэнтность не выполняется.

## 4. Пополнение по Кнуту-Бендиксу.

Фундированный порядок оставим из доказательства завершимости для системы без цикла, т.е. нужно перевернуть $\text{abb} \to \text{abaaaa}$.

Рассмотрим критическую пару $\langle\text{babb}, \text{bbab}\rangle$, получаемую при применении $\text{bbb} \to \text{bab}$ к $\text{bbbb}$. $\text{babb}$ сходится к НФ $\text{abb}$, $\text{bbab}$ - к $\text{bab}$. Тогда, в соответствии с имеющимся порядком, добавляем $\text{abb} \to \text{bab}$. 

$\text{abba}$ образует критические пары $\langle\text{baba}, \text{aba}\rangle$. Добавим правило $\text{baba} \to \text{aba}$. Им можно заменить $\text{abba} \to \text{aba}$, тем более что LHS меньше.

$\text{ababa}$ образует критические пары $\langle\text{baba}, \text{aaba}\rangle$. $\text{baba}$ сходится к $\text{aba}$. Добавим правило $\text{aaba} \to \text{aba}$.

$\text{aaaba}$ образует критические пары $\langle\text{bba}, \text{aaba}\rangle$. $\text{aaba}$ сходится к $\text{aba}$. Добавим правило $\text{bba} \to \text{aba}$. Правила $\text{bbab} \to \text{bab}$, $\text{aaaba} \to \text{bba}$ можно удалить. 

$\text{bbaaaa}$ образует критические пары $\langle\text{abaaaa}, \text{bb}\rangle$. $\text{abaaaa}$ сходится к $\text{bab}$. Добавим правило $\text{bab} \to \text{bb}$. Правила $\text{baba} \to \text{aba}$, $\text{bbaaaa} \to \text{bb}$ можно удалить.

$\text{bbaaab}$ образует критические пары $\langle\text{abaaab}, \text{aaaab}\rangle$. $\text{abaaab}$ сходится к $\text{ab}$. Добавим правило $\text{aaaab} \to \text{ab}$. Правила $\text{baaaab} \to \text{bab}$, $\text{aaaabb} \to \text{bb}$, $\text{bbaaab} \to \text{aaaab}$ можно удалить.

$\text{baaabb}$ образует критические пары $\langle\text{baaabb}, \varepsilon\rangle$. $\text{baaabb}$ сходится к $\text{bb}$. Добавим правило $\text{bb} \to \varepsilon$. Правила $\text{baaabb} \to \varepsilon$ можно удалить.

$\text{baabaab}$ образует критические пары $\langle\text{babaab}, \text{baaab}\rangle$. $\text{babaab}$ сходится к $\text{abaab}$. Добавим правило $\text{abaab} \to \text{baaab}$. Правила $\text{baabaab} \to \text{baaab}$ можно удалить.

Новая критическая пара из $\text{bbaaab}$: $\langle\text{aaab}, \text{abaaab}\rangle$. $\text{abaaab}$ сходится к $\text{ab}$. Добавим правило $\text{aaab} \to \text{ab}$.

Новая критическая пара из $\text{abaaab}$: $\langle\text{abab}, \text{ab}\rangle$. $\text{abab}$ сходится к $\varepsilon$. Добавим правило $\text{ab} \to \varepsilon$. $\text{abab} \to \text{bab}$, $\text{abaaab} \to \text{ab}$ можно удалить.

Заменим $\text{abaaaa}$ на $\text{aaaa}$ (критическая пара $\langle\text{aaaa}, \text{abb}\rangle$).

Критические пары из $\text{abb}$: $\langle\text{a}, \text{bab}\rangle$, $\langle\text{b}, \text{bab}\rangle$. Cистема сводится к тривиальной:

$$
\left\lbrace
\begin{array}{lr}
\text{a} \to \varepsilon \\
\text{b} \to \varepsilon
\end{array}
\right.
=
T'.
$$

В таком случае пополним систему без $\varepsilon$-правила. До разбора критической пары с эпсилоном:

$$
\left\lbrace
  \begin{array}{lr}
    \text{abaab} \to \text{baaab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{bb} \\
    \text{bba} \to \text{aba} \\
    \text{aaba} \to \text{aba} \\
    \text{abb} \to \text{bb} \\
    \text{bbb} \to \text{bb} \\
    \text{abab} \to \text{bb} \\
    \text{babb} \to \text{abb} \\
    \text{aaaaa} \to \text{a} \\
    \text{abaaaa} \to \text{bb}\\
    \text{abaaab} \to \text{ab} \\
    \text{babaaba} \to \text{bb} \\
    \text{babaabb} \to \text{babaaa}
\end{array}
\right. 
$$

$\text{babaaba}$ порождает критическую пару $\langle\text{bbaaba}, \text{bb}\rangle$. $\text{bbaaba}$ сходится к $\text{aba}$.　Добавим правило $\text{aba} \to \text{bb}$. Тогда правило $\text{aaba} \to \text{aba}$ выводится из других правил, его можно убрать.

$$
\left\lbrace
  \begin{array}{lr}
    \text{abaab} \to \text{baaab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{bb} \\
    \text{bba} \to \text{bb} \\
    \text{abb} \to \text{bb} \\
    \text{bbb} \to \text{bb} \\
    \text{abab} \to \text{bb} \\
    \text{babb} \to \text{bb} \\
    \text{aaaaa} \to \text{a} \\
    \text{abaaaa} \to \text{bb}\\
    \text{abaaab} \to \text{ab} \\
    \text{aba} \to \text{bb} \\
    \text{babaabb} \to \text{babaaa}
\end{array}
\right. 
$$

$\text{abaab}$ порождает критическую пару $\langle\text{bbab}, \text{baaab}\rangle$. $\text{bbab}$ сходится к $\text{bb}$. Тогда заменим $\text{abaab} \to \text{baaab}$ правилом $\text{baaab} \to \text{bb}$.

Теперь $\text{abaaab}$ порождает критическую пару $\langle\text{abb}, \text{ab}\rangle$. $\text{abb}$ сходится к $\text{bb}$. Значит, заменим $\text{abaaab} \to \text{ab}$ правилом $\text{bb} \to \text{ab}$.

$$
\left\lbrace
  \begin{array}{lr}
    \text{baaab} \to \text{bb} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{bb} \\
    \text{bba} \to \text{bb} \\
    \text{abb} \to \text{bb} \\
    \text{bbb} \to \text{bb} \\
    \text{abab} \to \text{bb} \\
    \text{babb} \to \text{bb} \\
    \text{aaaaa} \to \text{a} \\
    \text{abaaaa} \to \text{bb}\\
    \text{bb} \to \text{ab} \\
    \text{aba} \to \text{bb} \\
    \text{babaabb} \to \text{babaaa}
\end{array}
\right. 
\to
\left\lbrace
  \begin{array}{lr}
    \text{baaab} \to \text{ab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{ab} \\
    \text{abb} \to \text{ab} \\
    \text{bbb} \to \text{ab} \\
    \text{aaaaa} \to \text{a} \\
    \text{bb} \to \text{ab} \\
    \text{aba} \to \text{ab} \\
    \text{babaabb} \to \text{babaaa}
\end{array}
\right.
$$

$\text{babaabb}$ порождает критические пары $\langle\text{abaabb}, \text{babaaa}\rangle$, $\langle\text{bababb}, \text{babaaa}\rangle$, $\langle\text{babaab}, \text{babaaa}\rangle$. Все части этих пар сходятся к $\text{ab}$, можно убрать. 

$$
\left\lbrace
  \begin{array}{lr}
    \text{baaab} \to \text{ab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{ab} \\
    \text{abb} \to \text{ab} \\
    \text{bbb} \to \text{ab} \\
    \text{aaaaa} \to \text{a} \\
    \text{bb} \to \text{ab} \\
    \text{aba} \to \text{ab} \\
\end{array}
\right.
\to
\left\lbrace
  \begin{array}{lr}
    \text{baaab} \to \text{ab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{ab} \\
    \text{abb} \to \text{ab} \\
    \text{aaaaa} \to \text{a} \\
    \text{bb} \to \text{ab} \\
    \text{aba} \to \text{ab} \\
\end{array}
\right.
$$

$\text{aaaaab}$ порождает критическую пару $\text{ab}, \text{aab}$. Добавим правило $\text{aab} \to \text{ab}$.

$$
\left\lbrace
  \begin{array}{lr}
    \text{baaab} \to \text{ab} \\
    \text{aaaab} \to \text{ab} \\
    \text{bab} \to \text{ab} \\
    \text{abb} \to \text{ab} \\
    \text{aaaaa} \to \text{a} \\
    \text{bb} \to \text{ab} \\
    \text{aba} \to \text{ab} \\
    \text{aab} \to \text{ab} \\
\end{array}
\right.
\to
\left\lbrace
  \begin{array}{lr}
    \text{bab} \to \text{ab} \\
    \text{aba} \to \text{ab} \\
    \text{aaaaa} \to \text{a} \\
    \text{bb} \to \text{ab} \\
    \text{aab} \to \text{ab} \\
\end{array}
\right.
=
T''.
$$

Данная система конфлюэнтна и минимальна. Ни одно правило нельзя получить из других. Заметим, что $\text{ab}$ поглощает все символы слева и справа. Ни одно из правил нельзя изменить на правило с меньшим LHS без потери этого свойства, более того, LHS $\text{bb}$ - наименьшее слово, не являющееся НФ. 


## 5. Инварианты.

Поскольку длина слова при переписывании не возрастает и существует конечное число нормальных форм конечной длины, то приведённые ниже инварианты будут монотонно уменьшаться при применении правил. Они справедливы для $T_{term}$, $T'$ и $T''$ (пополнение без $\varepsilon$-правила).

1. Длина слова.
2. $\sum_{i} M(w_i)$  (при $\dfrac{1}{3} \leq \dfrac{W(\text{a})}{W(\text{b})} \leq 1$).
3. Лексикографическая пара $(|w|, \sum_{i} M(w_i))$.

