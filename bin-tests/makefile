################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tests/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: clean js-compiler

# Tool invocations
js-compiler: $(OBJS) $(USER_OBJS)
	@echo $(OBJS) $(USER_OBJS) $(LIBS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	g++ -o "js-compiler" -D__BUILDOP_TST $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) js-compiler
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
