# RVO (Return Value Optimisation)
- Return Value Optimization (RVO) in C+ + is a compiler optimization that eliminates the creation of temporary objects by directly constructing the return value in the memory location of the caller.
- RVO comes as
	- NRVO (Named RVO)
		- NRVO Support is optional but recommended.
		
	- URVO (Un-named RVO)
		- Compilers are allowed to perform URVO from C++ 98.
		- However Compilers are **required** to perform URVO from C++ 17. 
- -no-elide-constructors for gcc and clang
- -fno-elide-constructors for msvc. 
	- MSVC disables NRVO by default.
The C++ standard allows an implementation to omit creating a temporary which is only used to initialize another object of the same type. Specifying this option disables that optimization, and forces G++ to call the copy constructor in all cases.
- MSVC disabled NRVO by default.

### When does RVO does not work.
- when it is disabled.
- When the object construction happens outside the scope of current function.
- When the return type is not same as what being returned. Types need to match.
- When there are multiple return statements returning different objects, this is specific to NRVO.
- When you are returning a complex expression, specific to NRVO.
- 
