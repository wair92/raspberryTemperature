
LINK_TARGET = temperature.bin
TEST_TARGET = run_tests.bin

# Here is a Make Macro that uses the backslash to extend to multiple lines.
OBJS =  \
 backup.o \
 config.o \
 temperature.o \
 timeformat.o \
 parser.o \
 main.o \

TEST_OBJS = \
 	temperature_unittest.o \
	parser_unittest.o \
	temperature.o \
	config.o \
	timeformat.o \
	parser.o \
	unittest_main.o \

# Here is a Make Macro defined by two Macro Expansions.
# A Macro Expansion may be treated as a textual replacement of the Make Macro.
# Macro Expansions are introduced with $ and enclosed in (parentheses).
REBUILDABLES = $(OBJS) $(LINK_TARGET) $(TEST_TARGET) $(TEST_OBJS)

# Here is a simple Rule (used for "cleaning" your build environment).
# It has a Target named "clean" (left of the colon ":" on the first line),
# no Dependencies (right of the colon),
# and two Commands (indented by tabs on the lines that follow).
# The space before the colon is not required but added here for clarity.
clean :
	rm -f $(REBUILDABLES)
	echo Clean done

# There are two standard Targets your Makefile should probably have:
# "all" and "clean", because they are often command-line Goals.
# Also, these are both typically Artificial Targets, because they don't typically
# correspond to real files named "all" or "clean".

# The rule for "all" is used to incrementally build your system.
# It does this by expressing a dependency on the results of that system,
# which in turn have their own rules and dependencies.
all : $(LINK_TARGET) $(TEST_TARGET)
	echo All done

# There is no required order to the list of rules as they appear in the Makefile.
# Make will build its own dependency tree and only execute each rule only once
# its dependencies' rules have been executed successfully.

# Here is a Rule that uses some built-in Make Macros in its command:
# $@ expands to the rule's target, in this case "test_me.exe".
# $^ expands to the rule's dependencies, in this case the three files
# main.o, test1.o, and  test2.o.
$(LINK_TARGET) : $(OBJS)
	gcc -g -o $@ $^ -lstdc++ -lpthread

$(TEST_TARGET) : $(TEST_OBJS)
	gcc -g -o $@ $^ -lstdc++ -lpthread -lgtest

# Here is a Pattern Rule, often used for compile-line.
# It says how to create a file with a .o suffix, given a file with a .cpp suffix.
# The rule's command uses some built-in Make Macros:
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
%.o : %.cpp
	gcc -g -o $@ -c $< -std=c++2a
