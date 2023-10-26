## A level-two header##

### A level-three header ###

As with setext-style headers, the header text can contain formatting:

# A level-one header with a [link](/C:\enterprise\pandoc-2.2.3.2\test\markdown.md) and *emphasis*

I like several of their flavors of ice cream:
# 22, for example, and #5.


> This is a block quote. This
> paragraph has two lines.
>
> 1. This is a list inside a block quote.
> 2. Second item.


> This is a block quote. This
paragraph has two lines.


> 1. This is a list inside a block quote.
2. Second item.

> This is a block quote.
>
> > A block quote within a block quote.

>     code


> This is a block quote.
>> Nested.

you can simply write

[Header identifiers in HTML]

or

[Header identifiers in HTML][]

or

[the section on header identifiers][header identifiers in
HTML]

instead of giving the identifier explicitly:

[Header identifiers in HTML](#header-identifiers-in-html)


    if (a > 3) {
      moveShip(5 * gravity, DOWN);
    }
	
	
~~~~~~~
if (a > 3) {
  moveShip(5 * gravity, DOWN);
}
~~~~~~~

Like regular code blocks, fenced code blocks must be separated from surrounding text by blank lines.

If the code itself contains a row of tildes or backticks, just use a longer row of tildes or backticks at the start and end:

~~~~~~~~~~~~~~~~
~~~~~~~~~~
code including tildes
~~~~~~~~~~
~~~~~~~~~~~~~~~~

Extension: backtick_code_blocks

Same as fenced_code_blocks, but uses backticks (`) instead of tildes (~).
Extension: fenced_code_attributes

Optionally, you may attach attributes to fenced or backtick code block using this syntax:

~~~~ {#mycode .haskell .numberLines startFrom="100"}
qsort []     = []
qsort (x:xs) = qsort (filter (< x) xs) ++ [x] ++
               qsort (filter (>= x) xs)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
Extension: line_blocks

A line block is a sequence of lines beginning with a vertical bar (|) followed by a space. The division into lines will be preserved in the output, as will any leading spaces; otherwise, the lines will be formatted as Markdown. This is useful for verse and addresses:

| The limerick packs laughs anatomical
| In space that is quite economical.
|    But the good ones I've seen
|    So seldom are clean
| And the clean ones so seldom are comical

| 200 Main St.
| Berkeley, CA 94718

The lines can be hard-wrapped if needed, but the continuation line must begin with a space.

| The Right Honorable Most Venerable and Righteous Samuel L.
  Constable, Jr.
| 200 Main St.
| Berkeley, CA 94718


* one
* two
* three

This will produce a “compact” list. If you want a “loose” list, in which each item is formatted as a paragraph, put spaces between the items:

* one

* two

* three

The bullets need not be flush with the left margin; they may be indented one, two, or three spaces. The bullet must be followed by whitespace.

List items look best if subsequent lines are flush with the first line (after the bullet):

* here is my first
  list item.
* and my second.

But Markdown also allows a “lazy” format:

* here is my first
list item.
* and my second.	

<table>
<tr>
<td>*one*</td>
<td>[a link](http://google.com)</td>
</tr>
</table>

into

<table>
<tr>
<td><em>one</em></td>
<td><a href="http://google.com">a link</a></td>
</tr>
</table>

<!-- comment -->

```javascript
function test() {
  console.log("notice the blank line before this function?");
}
```

