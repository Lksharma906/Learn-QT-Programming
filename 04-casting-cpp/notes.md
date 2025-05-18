# CPP Casting

- static_cast
- dynamic_cast
- reinterpret_cast
- const_cast

- They do not do anything which cannot be done by c-style cast.So interms it is not adding any additional functionality which c cannot do, but it is adding the syntax-coating on c-style casts. In a way it does extra things. 
---
### Benefits it offer
- Code searchiblity.

## Static_cast
- It performs implicit conversion between types. Meanining the conversion which happen at compile time.
- Use static_cast when conversion between types is provided through conversion operator or conversion constructor.
- static_cast is more restrictive than C-style casts.
        - char* to int* is allowed in c-style cast but not with static cast.
- static_cast avoid the cast from drived to private base pointer.

``` cpp
class Base {}
class Derived: private Base{};
int main() {
        Derived d1;
        Base *bp1 = (Base*) &d1; // Allowed at compile time.
        Base *bp2 = static_cast<Base*>(&d1); // Not allowed at compile time.

```
- Use for all upcasts, but never use for confused down cast.


#### 📌 **UML Diagram: `static_cast` — Upcast ✅ vs Downcast ❌**

```text
              +----------------+
              |   BaseClass    |
              +----------------+
                   ▲  ▲
                  /    \
        Upcast ✅ /      \ Downcast ❌ (confusing/unsafe)
                /        \
+----------------+    +----------------+
|  Derived1      |    |   Derived2     |
+----------------+    +----------------+

✔️ static_cast<BaseClass*>(new Derived1());   // SAFE (upcast)
❌ static_cast<Derived2*>(BaseClassPtr);       // DANGEROUS (confused downcast)
```

---

##### ✅ Safe Upcast:

```cpp
Derived1* d1 = new Derived1();
BaseClass* base = static_cast<BaseClass*>(d1); // OK
```

##### ❌ Confused Downcast:

```cpp
BaseClass* base = getSomeBase();
Derived2* d2 = static_cast<Derived2*>(base); // Danger! May crash
```

> Use `dynamic_cast` if you *must* downcast and want to ensure the type is correct at runtime:

```cpp
Derived2* d2 = dynamic_cast<Derived2*>(base);
if (d2) {
    // safe
}
```
- Static_cast to be prefered when converting from void* or to void*.
```cpp
void * v = static_cast(void*)(&i); // Here i is an int.
int * v = static_cast(int*)(v); // Here v is an void type.

```

## Const_cast

- The expression const_cast\<T>(v) can be used to change the **const or volatile** qualifiers of **pointer or references**.
- Where T must be a pointer , or pointer to a member type.
- To remove the constantness or volatileness of any variable.

```cpp
int main() {
        const int a1 = 10;
        const int *b1 = &a1;
        int *d1 = const_cast<int*>(b1);
        *d1 = 15; // Invalid and undefined behaviour.
        cout<< a1 << endl;// prints 10.
        cout<< *d1 << endl; // prints 15. Eventhough both are pointing to same location.
        
        // Valid example is below.
        int a2 = 20; // not a const.
        const int* b2 = &a2;
        int *d2 = const_cast<int*>(b2); 
        *d2 = 30;
}
```

```text
Memory Layout:
+-----------------------------+
| a1: const int               |
| Value: 10                   |
| Possibly in read-only mem  |
+-----------------------------+
         ▲
         |
+-----------------------------+
| b1: const int*              |
| Points to: a1               |
+-----------------------------+
         |
    const_cast
         v
+-----------------------------+
| d1: int*                    |
| Points to: a1               |
| ❌ Tries to modify const    |
+-----------------------------+

Result:
- *d1 = 15;* --> Undefined behavior!
- cout << a1;  // prints 10
- cout << *d1; // prints 15 (but invalid!)


- When we need to call a 3rd party lib where it is taking variable/object as non-const but not modifying it.

``` cpp
void 3pl(int* x) {
//doing some processing not modifying x.
}
int main(){
const int x = 10;
const int * px = &x;
3pl(const_cast<int*>(px)); // it removes the constantness.
```
- In above example we need to have this as the function cannot take a const value and compiler will through an error.
### Never use const cast
1. Use when you only need it.
2. Use when the actual object it refers is not const.
3. Use when dealing with 3rd party libs which are not changing the variable value.

---

## DYNAMIC_CAST

1. dynamic_cast is used at run_time to find the correct down-cast
2. Need at least one virtual function in base class.
3. If the cast is successfull , dynamic cast returns a value of new type.
4. if the cast fails and new_type is a pointer type, it returns a null pointer.
5. if the cast fails and new type is reference type, it throws and exception that matches a handler of type std::bad_cast.

- Work only on polymorphic code. because it need runtime information to detect correct downcast.
- As well as it has some run time overhead. Avoid if not necessary. Use static cast if you are sure of what is downcasted.


---
## REINTERPRET_CAST
- can cast to any type , this is an instruction to complier to trust me i know what i am doing.
- you can cast a struct to an int type and perform pointer arithematic on that.
- It is non-portable in nature.
- if it is repinterpret_casted then do cast it back to orignal else it is not much useful.







