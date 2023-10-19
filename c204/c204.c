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
	// Loops while stack is not empty
	while (!Stack_IsEmpty(stack)) {
		// Gets value from top and pops
		Stack_Top(stack, &c);
		Stack_Pop(stack);

		if (c == '(')
			break;

		// Adds popped char to postfix expression
		postfixExpression[(*postfixExpressionLength)++] = c;
	}
}

/// @brief Gets presedence of the given operator
/// @param op operator to get presedence of
/// @return	presedence
int presedence(char op) {
	switch (op) {
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
	// Pops all operators from stack with greater or equal presedence
	char op;
	while (!Stack_IsEmpty(stack)) {
		Stack_Top(stack, &op);
		if (presedence(c) > presedence(op))
			break;

		postfixExpression[(*postfixExpressionLength)++] = op;
		Stack_Pop(stack);
	}

	// Pushes current operator to stack
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
	// Allocates memory for postfix string, checks if allocated properly
	char *postfix = malloc(sizeof(*postfix) * MAX_LEN);
	if (!postfix)
		return NULL;

	// Creates stack for operators
	Stack ops;
	Stack_Init(&ops);

	// Main loop containing infix to postfix parsing, calls specific functions
	unsigned cur = 0;
	for (int i = 0; infixExpression[i] != '='; ++i) {
		if (presedence(infixExpression[i]))
			doOperation(&ops, infixExpression[i], postfix, &cur);
		else if (infixExpression[i] == '(')
			Stack_Push(&ops, infixExpression[i]);
		else if (infixExpression[i] == ')')
			untilLeftPar(&ops, postfix, &cur);
		else
			postfix[cur++] = infixExpression[i];
	}

	// Pops remaining operators
	untilLeftPar(&ops, postfix, &cur);
	// Adds equals and end of string characters
	postfix[cur++] = '=';
	postfix[cur] = '\0';

	// Frees stack
	Stack_Dispose(&ops);

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
	// Pushes sizeof(value) bytes of number (more generic than using 4 bytes)
	// Value has to be shifted and then masked
	for (int i = sizeof(value) - 1; i >= 0 ; --i) {
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
	*value = 0;
	char c;
	// Gets sizeof(*value) bytes of number (more generic then using 4 bytes)
	// Pops from stack, shifts popped value and does bit or to get final value
	for (int i = 0; i < (int)sizeof(*value); ++i) {
		Stack_Top(stack, &c);
		Stack_Pop(stack);
		*value |= c << i * 8;
	}
}


bool var_value(VariableValue* values, int cnt, char var, int *val) {
	for (int i = 0; i < cnt; ++i) {
		if (values[i].name == var) {
			*val = values[i].value;
			return true;
		}
	}
	return false;
}

/// @brief Calculates next operation
/// @param stack stack containing numbers
/// @param op operation to calculate with
/// @param res pointer to int that result will be saved to
/// @return true on success, else false
bool calc(Stack *stack, char op, int *res) {
	// Gets two numbers from stack
	int x, y;
	expr_value_pop(stack, &y);
	expr_value_pop(stack, &x);

	// Calculates based on operator
	switch (op) {
		case '+':
			*res = x + y;
			return true;
		case '-':
			*res = x - y;
			return true;
		case '*':
			*res = x * y;
			return true;
		case '/':
			// Checks zero division
			if (y == 0)
				return false;
			*res = x / y;
			return true;
		default:
			return false;
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
	// Numbers stack initialization
	Stack nums;
	Stack_Init(&nums);

	// Gets postfix and evaluates it
	char *postfix = infix2postfix(infixExpression);
	int v;
	for (int i = 0; postfix && postfix[i] != '='; ++i) {
		// Pushes calculated value to stack based on current operator
		if (presedence(postfix[i])) {
			// Returns false when zero division or unknown operation
			if (!calc(&nums, postfix[i], &v))
				return false;
			expr_value_push(&nums, v);
		}
		// Pushes digit to stack when digit
		else if (postfix[i] >= '0' && postfix[i] <= '9') {
			expr_value_push(&nums, postfix[i] - '0');
		}
		// Gets variable value and pushes it to stack
		else {
			if (!var_value(variableValues, variableValueCount, postfix[i], &v))
				return false;
			expr_value_push(&nums, v);
		}
	}

	// Gets result stored in stack
	expr_value_pop(&nums, value);

	// If stack is not empty, returns false
	bool res = Stack_IsEmpty(&nums);
	// Frees stack and postfix string
	Stack_Dispose(&nums);
	free(postfix);

	return res;
}

/* Konec c204.c */
