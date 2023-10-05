# IAL DU1

V první domácí úloze, na Vás čekají následující tři příklady:

1. **C202**: implementace zásobníku znaků v dynamickém poli *(až 2 body)*,
2. **C204**: převod výrazů z infixové do postfixové notace a jejich
vyhodnocení *(až 4 body)*,
3. **C206**: implementace dvousměrně vázaného lineárního seznamu *(až 4 body)*.

Vaším úkolem je doplnit těla funkcí v souborech `c202.c`, `c204.c` a `c206.c` a
tyto tři soubory následně odevzdat prostřednictvím STUDISu *(nezabalené a v
kódování v UTF-8)*.

Správnost Vašich implementací si můžete částečně ověřit pomocí základních
testovacích aplikací *(např. `c202-test.c`)*, pro jejichž překlad máte
předpřipraveny i soubory Makefile *(`make all`, `make clean`, `make run`)*.
Pozn.: do hlaviček funkcí ani do předpřipravených hlavičkových souborů, prosím,
nezasahujte!

Jestliže Vaše implementace daného příkladu generuje správné výsledky pro
základní testovací aplikaci, při překladu a spuštění na serveru
`eva.fit.vutbr.cz` (správné výsledky, které najdete např. v souboru
`c202-test.out`, jež můžete s výstupy vaší aktuální implementace snadno
porovnat spuštěním make run), získáváte za příklad **1 bod**. Jestliže Vaše
implementace vyhoví i pokročilým
testům *(ty v zadání domácí úlohy nenajdete)*, získáváte za příklad i zbývající
body (tedy **1 bod** za příklad **C202** a **3 body** za příklad
**C204 a C206**).

Doporučuji Vám proto, abyste si zkusili základní testovací aplikaci rozšířit
a odhalit tak co nejvíce chyb ve své implementaci ještě před samotným
hodnocením. Případnou upravenou testovací aplikaci ale do STUDISu
neodevzdávejte.

Pokud se dostanete do časové tísně, nesnažte se řešit všechny příklady
najednou v naději, že za částečné řešení něco dostanete. V takovém případě je
výhodnější dokončit alespoň jeden či dva příklady pořádně. Hodnocení je
striktní a sebemenší počet chyb vede ke ztrátě značného množství bodů.

**Důležitá upozornění!**

Domácí úlohy budou překládány, spouštěny a hodnoceny automatickými skripty na
serveru `eva.fit.vutbr.cz`. Nedodržení zadání (např. zásahy do kostry programu)
bude mít za následek ztrátu všech bodů za domácí úlohu! Bodovou ztrátou budou
dále postiženy projekty bez vhodných komentářů. Termín konzultací/případných
reklamací hodnocení bude zveřejněn v hodnotícím emailu.

Stejně tak budou 0 body hodnoceny příklady nepřeložitelné a ty, které se
nekonečně zacyklí - příklad se se zlou potáže (přesněji řečeno s kill -9),
pokud bude potřebovat k řešení více jak 15s.

Domácí úlohu vypracovávejte, prosím, samostatně a své řešení nikde volně
nepublikujte! V případě odhalení plagiátorství či nedovolené spolupráce
nebude udělen zápočet a dále bude zváženo zahájení disciplinárního řízení.

Případné dotazy primárně nesměřujte na garanta předmětu ani přednášející ale
na vedoucího zadání a to prostřednictvím fakultního emailu a nebo
korespondujícího diskusního fóra.
