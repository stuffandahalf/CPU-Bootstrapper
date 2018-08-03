AS=~/Desktop/6809-computer/as9/as9
AFLAGS=-now l s19

sum_test.s19 sum_test.lst: sum_test.s
	$(AS) $< $(AFLAGS)

.PHONY: clean
clean:
	rm -f sum_test.s19
	rm -f sum_test.lst
