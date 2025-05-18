# QScopedPointer

A `QScopedPointer` **cannot be passed by copy** because it is a **non-copyable** smart pointer. This is **by design**, and here's why:

---

### 🧠 **Key Concept: Ownership**

`QScopedPointer` is designed to **strictly manage ownership** of a dynamically allocated object. When a `QScopedPointer` goes out of scope, it **automatically deletes** the object it holds. It ensures that **only one owner** exists at any time.

---

### ❌ Why Copying is Disabled

If copying were allowed:

* You could have **two `QScopedPointer`s pointing to the same object**.
* When both go out of scope, the object would be deleted **twice**, leading to **undefined behavior** (crashes, memory corruption).

---

### ✅ Alternative: Move Semantics (C++11 and later)

`QScopedPointer` **can be moved**, meaning you can **transfer ownership**, but not duplicate it.

```cpp
QScopedPointer<MyObject> a(new MyObject);
QScopedPointer<MyObject> b = std::move(a); // OK: ownership moves to b
```

After this, `a` becomes null, and only `b` owns the object.

---

### ✅ What to Use If You Need Copy Semantics

* Use `QSharedPointer` if you need **reference-counted shared ownership**.
* Use raw pointers with manual memory management (not recommended).
* Use `QPointer` for QObject-based objects with automatic nullification on deletion.

---

### 🔒 Summary

| Smart Pointer    | Copyable? | Purpose                          |
| ---------------- | --------- | -------------------------------- |
| `QScopedPointer` | ❌ No      | Exclusive ownership, auto-delete |
| `QSharedPointer` | ✅ Yes     | Shared ownership, ref-counted    |
| `QPointer`       | ✅ Yes     | Weak pointer for QObjects        |

---


## ✅ Example: Transferring Ownership of a `QScopedPointer`

### Step 1: Define a class

```cpp
class MyObject {
public:
    MyObject() { qDebug() << "MyObject created"; }
    ~MyObject() { qDebug() << "MyObject destroyed"; }
    void doWork() { qDebug() << "Doing some work"; }
};
```

---

### Step 2: Function that takes ownership

```cpp
void processObject(QScopedPointer<MyObject> obj) {
    if (obj) {
        obj->doWork();
    }
    // obj is destroyed automatically at the end of this function
}
```

> Since `QScopedPointer` is non-copyable, we must **move** it into the function.

---

### Step 3: Calling the function with `std::move`

```cpp
int main() {
    QScopedPointer<MyObject> ptr(new MyObject);

    // Transfer ownership to the function
    processObject(std::move(ptr));

    // ptr is now null
    if (ptr.isNull()) {
        qDebug() << "ptr is null after move";
    }

    return 0;
}
```

---

### 🔑 What Happens

* `MyObject` is created and owned by `ptr`.
* `std::move(ptr)` transfers ownership to `processObject()`.
* At the end of `processObject()`, the object is destroyed automatically.
* `ptr` becomes null after the move.

---

### 🔁 If You Want to Keep a Copy:

Use `QSharedPointer` instead:

```cpp
void processShared(QSharedPointer<MyObject> obj) {
    obj->doWork();  // obj is a shared copy
}

int main() {
    QSharedPointer<MyObject> sharedPtr = QSharedPointer<MyObject>::create();
    processShared(sharedPtr);  // Safe copy
    processShared(sharedPtr);  // Safe again
}
```

---

