CC= gcc
FLAGS= -Wall -g


all: policy

policy: set_policy.c
	$(CC) $(FLAGS) -o policy set_policy.c

.PHONY:

clean:
	rm -f policy
