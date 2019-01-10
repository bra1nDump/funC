`funC library` 
===

Build with emacs <img src="https://shop.fsf.org/sites/default/files/styles/product_zoom/public/Emacs-icon.sh_.png" width="100" height="100" />

This library attempts to make programming in a functional style
simpler in C. In other words it tries to make programming
in `C` fun. It was inspired by functional-first languages:

* `Haskell`
* `F#`
* `Elixir`
* `LISP`

Who is this for?
---

Students, in whom the spark of functional programming
was lit at, would want to use this library for having more fun
taking courses that require to write `C` code.


Wait, why?
---

After coding a couple of CS assignments as well as using them
at a day job functional style of programming appealed to me a lot,
and now having to go back to the old `C` really bothered me. Things
that bother me the most are:

* Weird standard library, as well as relatively bad `namespacing` (like std in `c++`)
* Low level memory managment
* Poor generic programming tooling
* No first class support for functions

What does the library do?
---

* Implements `modules` like `List, Array, Map, System` that have nice namespacing for
working with associated types
* Attempts to simplify memory managment using `Box` and container `free`
  (more on this later in the document)
* Uses `Box` abstraction to store any data structures.
  Is based on `void *` pointers and `memcpy`
* Implements `map, fold, show` in every container module

<img src="https://cdn.shopify.com/s/files/1/0402/9449/products/torvalds.png?v=1406355999" width="200" height="200" />

Examples
---

```C
box square(void* xVoidPointer) {
	int xInt = *((int*) xVoidPointer);
	int newContents = xInt * xInt;
	return Box.box(sizeof(int), &newContents);
}

void printInt(void* xVoidPointer) {
	printf("%d\n", *((int*) xVoidPointer));
}

int main() {
	List.map_
		( printInt
		, List.map
			( square
			, List.integerRange(1, 10)));
}

```

Did I just create an integer list from a range, mapped
over it and printed it out all in one statement?

Yes you did! We promissed you `fun`ctional C!


What does the library not do?
---

* Make you a decent functional programmer overnight
* Solve any of the above listed limitations of `C` entirely

Contribute
---

All contributions are welcome!

If anyone has any info on simmilar libraries or why this idea
is doomed for failure, please reach out.

General thoughts
---

I do not know how useful this library can actually be
, but I want to find out by applying it to the homeworks
of cs 111 at UCLA winter 19 semester taught by proffessor Eggert.


References
---

https://lucabolognese.wordpress.com/2013/01/04/functional-programming-in-c/#discriminated-unions-in-c
