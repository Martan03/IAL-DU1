#include "c204.h"
#include "c204-test-utils.h"

#include <stdio.h>
#include <stdlib.h>

#define TEST_COUNT ((long int) (sizeof(tests) / sizeof(void *)))


TEST(test_01, "Upper and lower case characters with plus operator")
	if (convert("a+B=", &expr))
	{
		verify(expr, "aB+=");
	}
ENDTEST

TEST(test_02, "Digits with minus operator")
	if (convert("0-1=", &expr))
	{
		verify(expr, "01-=");
	}
ENDTEST

TEST(test_03, "Mixed operands with multiplication operator")
	if (convert("a*0=", &expr))
	{
		verify(expr, "a0*=");
	}
ENDTEST

TEST(test_04, "Mixed operands with division operator")
	if (convert("B/1=", &expr))
	{
		verify(expr, "B1/=");
	}
ENDTEST

TEST(test_05, "Simple parentheses support")
	if (convert("(a+b)=", &expr))
	{
		verify(expr, "ab+=");
	}
ENDTEST

TEST(test_06, "Expression evaluation from the left to the right")
	if (convert("a+b+c=", &expr))
	{
		verify(expr, "ab+c+=");
	}
ENDTEST

TEST(test_07, "Minus operator does not have higher priority than plus")
	if (convert("a+b-c=", &expr))
	{
		verify(expr, "ab+c-=");
	}
ENDTEST

TEST(test_08, "Plus operator does not have higher priority than minus")
	if (convert("A-B+C=", &expr))
	{
		verify(expr, "AB-C+=");
	}
ENDTEST

TEST(test_09, "Plus operator does not have higher priority than minus")
	if (convert("1*2/3=", &expr))
	{
		verify(expr, "12*3/=");
	}
ENDTEST

TEST(test_10, "Parentheses change operator priority")
	if (convert("A+(B-c)=", &expr))
	{
		verify(expr, "ABc-+=");
	}
ENDTEST

TEST(test_11, "Long expression")
	if (convert("A*B*C*D*E+F=", &expr))
	{
		verify(expr, "AB*C*D*E*F+=");
	}
ENDTEST

TEST(test_12, "Loop checker")
	if (convert("A+B*C*D-E=", &expr))
	{
		verify(expr, "ABC*D*+E-=");
	}
ENDTEST

TEST(test_13, "A lot of brackets")
	if (convert("(E*((A+B)*C+D)+F)*G+H=", &expr))
	{
		verify(expr, "EAB+C*D+*F+G*H+=");
	}
ENDTEST

TEST(test_14, "Invalid infix")
	if (convert("A+B ", &expr))
	{
		verify(expr, "AB+");
	}
ENDTEST

TEST(test_15, "Expression 1")
	if (convert("(A+B)*(C-D)=", &expr))
	{
		verify(expr, "AB+CD-*=");
	}
ENDTEST

TEST(test_16, "Expression 2")
	if (convert("A*B+C/D-E=", &expr))
	{
		verify(expr, "AB*CD/+E-=");
	}
ENDTEST

TEST(test_17, "Expression 3")
	if (convert("A+B*C-D/E=", &expr))
	{
		verify(expr, "ABC*+DE/-=");
	}
ENDTEST

TEST(test_18, "Expression 4")
	if (convert("A+2*B-4/C=", &expr))
	{
		verify(expr, "A2B*+4C/-=");
	}
ENDTEST

TEST(test_19, "Expression 5")
	if (convert("((a+b))=", &expr))
	{
		verify(expr, "ab+=");
	}
ENDTEST

TEST(test_eval_01, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "(a+b)*(c-d)=";
	VariableValue values[] = {
			{'a', 5},
			{'b', 5},
			{'c', 12},
			{'d', 2},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_02, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "(a-b)*C=";
	VariableValue values[] = {
			{'a', 3},
			{'b', 5},
			{'C', -5},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_03, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "a*b+c/d=";
	VariableValue values[] = {
			{'a', 10},
			{'b', 3},
			{'c', 100},
			{'d', 5},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_04, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "a*b+c/d=";
	VariableValue values[] = {
			{'a', 10},
			{'b', 3},
			{'c', 100},
			{'d', 0},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_05, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "A*B+C/D-5=";
	VariableValue values[] = {
			{'A', 10},
			{'B', 3},
			{'C', 100},
			{'D', 0},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_06, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "A*(2+C/(D-5))=";
	VariableValue values[] = {
			{'A', 10},
			{'B', 3},
			{'C', 100},
			{'D', 15},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_07, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "(E*((A+B)*C+D)+F)*G+H=";
	VariableValue values[] = {
			{'A', 10},
			{'B', 3},
			{'C', 100},
			{'D', 15},
			{'E', 2},
			{'F', 5},
			{'G', 3},
			{'H', 99},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_08, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "A+B=";
	VariableValue values[] = {
			{'A', 536870911},
			{'B', 5},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST

TEST(test_eval_09, "Evaluate expression")
	STACK_SIZE = 128;
	expr = "A+B=";
	VariableValue values[] = {
			{'A', -536870911},
			{'B', 5},
	};
	PRINT_EXPR_EVAL_CONFIG();
	if (eval(expr, values, valuesCount, &result) == false) {
		FAIL("eval() call returned false\n");
	}
	printf("eval result: %d\n", result);
ENDTEST


void (*tests[])(void) = {
		test_01,
		test_02,
		test_03,
		test_04,
		test_05,
		test_06,
		test_07,
		test_08,
		test_09,
		test_10,
		test_11,
		test_12,
		test_13,
		test_14,
		test_15,
		test_16,
		test_17,
		test_18,
		test_19,
		test_eval_01,
		test_eval_02,
		test_eval_03,
		test_eval_04,
		test_eval_05,
		test_eval_06,
		test_eval_07,
		test_eval_08,
		test_eval_09,
};

int main( int argc, char *argv[] ) {
	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [test_id]\n", argv[0]);
		return 1;
	}

	char *test_id_reminder = NULL;
	long test_id;
	if (argc == 2)
	{
		test_id = strtol(argv[1], &test_id_reminder, 10);
		if (test_id_reminder[0] != 0)
		{
			fprintf(stderr, "Usage: %s {test_id}\n", test_id_reminder);
			fprintf(stderr, "Unexpected test_id: %s\n", test_id_reminder);
			return 1;
		}

		if (test_id < 0)
		{
			test_id = TEST_COUNT + test_id;
		}

		if (test_id + 1 > TEST_COUNT)
		{
			fprintf(stderr, "Unknown test: %ld (test count: %ld)\n", test_id, TEST_COUNT);
			return 1;
		}

		tests[test_id]();
	}
	else
	{
		printf("C204 - Infix to Postfix Expression Conversion, Basic Tests\n");
		printf("==========================================================\n");

		for (test_id = 0; test_id < TEST_COUNT; test_id++)
		{
			tests[test_id]();
		}
	}

	return 0;
}

/* Konec c204-test.c */
