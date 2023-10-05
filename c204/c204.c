/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"
#include <ctype.h>

bool solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void untilLeftPar( Stack *stack, char *postfixExpression, unsigned *postfixExpressionLength ) {
	char c;
	while (!Stack_IsEmpty(stack)) {
		Stack_Top(stack, &c);
		Stack_Pop(stack);

		if (c == '(')
			break;

		postfixExpression[*postfixExpressionLength] = c;
		++*postfixExpressionLength;
	}
}

/// @brief Gets presedence of the given operator
/// @param c operator to get presedence of
/// @return	presedence
int presedence(char c) {
	switch (c) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return 0;
	}
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation( Stack *stack, char c, char *postfixExpression, unsigned *postfixExpressionLength ) {
	if (Stack_IsEmpty(stack)) {
		Stack_Push(stack, c);
		return;
	}

	char op;
	Stack_Top(stack, &op);

	while (presedence(op) >= presedence(c)) {
		postfixExpression[*postfixExpressionLength] = op;
		++*postfixExpressionLength;
		Stack_Pop(stack);

		if (Stack_IsEmpty(stack))
			break;
		Stack_Top(stack, &op);
	}

	Stack_Push(stack, c);
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
 * řetězce konstantu NULL.
 *
 * @param infixExpression vstupní znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix( const char *infixExpression ) {
	char *postfix = malloc(sizeof(postfix) * MAX_LEN);
	if (!postfix)
		return NULL;

	unsigned cur = 0;
	Stack ops;
	Stack_Init(&ops);
	for (int i = 0; infixExpression[i]; ++i) {
		if (presedence(infixExpression[i]))
			doOperation(&ops, infixExpression[i], postfix, &cur);
		else if (infixExpression[i] == '(')
			Stack_Push(&ops, infixExpression[i]);
		else if (infixExpression[i] == ')')
			untilLeftPar(&ops, postfix, &cur);
		else
			postfix[cur++] = infixExpression[i];
	}

	--cur;
	untilLeftPar(&ops, postfix, &cur);

	Stack_Dispose(&ops);

	postfix[cur++] = '=';
	postfix[cur] = '\0';

	return postfix;
}


/**
 * Pomocná metoda pro vložení celočíselné hodnoty na zásobník.
 *
 * Použitá implementace zásobníku aktuálně umožňuje vkládání pouze
 * hodnot o velikosti jednoho byte (char). Využijte této metody
 * k rozdělení a postupné vložení celočíselné (čtyřbytové) hodnoty
 * na vrchol poskytnutého zásobníku.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value hodnota k vložení na zásobník
 */
void expr_value_push( Stack *stack, int value ) {
	for (int i = 3; i >= 0 ; --i) {
		Stack_Push(stack, value >> i * 8 & 0xff);
	}
}

/**
 * Pomocná metoda pro extrakci celočíselné hodnoty ze zásobníku.
 *
 * Využijte této metody k opětovnému načtení a složení celočíselné
 * hodnoty z aktuálního vrcholu poskytnutého zásobníku. Implementujte
 * tedy algoritmus opačný k algoritmu použitému v metodě
 * `expr_value_push`.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné celočíselné hodnoty z vrcholu zásobníku
 */
void expr_value_pop( Stack *stack, int *value ) {
	char c;
	*value = 0;
	for (int i = 0; i < 4; ++i) {
		Stack_Top(stack, &c);
		Stack_Pop(stack);
		*value |= c << i * 8;
	}
}

/// @brief Finds variable value
/// @param values array containing variables and its values
/// @param cnt values array length
/// @param var variable to find its value
/// @return value of the given variable
int var_value(VariableValue* values, int cnt, char var) {
	for (int i = 0; i < cnt; ++i) {
		if (values[i].name == var) {
			return values[i].value;
		}
	}
	return 0;
}

/// @brief Calculates next operation
/// @param stack stack containing numbers
/// @param op operation to calculate with
/// @return result of the operation
int calc(Stack *stack, char op) {
	int x, y;
	expr_value_pop(stack, &y);
	expr_value_pop(stack, &x);

	switch (op) {
		case '+':
			//printf("%d + %d = %d\n", x, y, x + y);
			return x + y;
		case '-':
			//printf("%d - %d = %d\n", x, y, x - y);
			return x - y;
		case '*':
			//printf("%d * %d = %d\n", x, y, x * y);
			return x * y;
		case '/':
			//printf("%d / %d = %d\n", x, y, x / y);
			return x / y;
		default:
			return 0;
	}
}

/**
 * Tato metoda provede vyhodnocení výrazu zadaném v `infixExpression`,
 * kde hodnoty proměnných použitých v daném výrazu jsou definovány
 * v poli `variableValues`.
 *
 * K vyhodnocení vstupního výrazu využijte implementaci zásobníku
 * ze cvičení c202. Dále také využijte pomocných funkcí `expr_value_push`,
 * respektive `expr_value_pop`. Při řešení si můžete definovat libovolné
 * množství vlastních pomocných funkcí.
 *
 * Předpokládejte, že hodnoty budou vždy definovány
 * pro všechy proměnné použité ve vstupním výrazu.
 *
 * @param infixExpression vstpní infixový výraz s proměnnými
 * @param variableValues hodnoty proměnných ze vstupního výrazu
 * @param variableValueCount počet hodnot (unikátních proměnných
 *   ve vstupním výrazu)
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné hodnoty vyhodnocení vstupního výrazu
 *
 * @return výsledek vyhodnocení daného výrazu na základě poskytnutých hodnot proměnných
 */
bool eval( const char *infixExpression, VariableValue variableValues[], int variableValueCount, int *value ) {
	// Stack initialization
	Stack nums;
	Stack_Init(&nums);

	char *postfix = infix2postfix(infixExpression);
	for (int i = 0; postfix && postfix[i] != '='; ++i) {
		if (presedence(postfix[i])) {
			expr_value_push(&nums, calc(&nums, postfix[i]));
		} else if (isdigit(postfix[i])) {
			expr_value_push(&nums, postfix[i] - '0');
		} else {
			int v = var_value(variableValues, variableValueCount, postfix[i]);
			expr_value_push(&nums, v);
		}
	}

	expr_value_pop(&nums, value);

	bool res = Stack_IsEmpty(&nums);
	Stack_Dispose(&nums);
	free(postfix);

	return res;
}

/* Konec c204.c */
