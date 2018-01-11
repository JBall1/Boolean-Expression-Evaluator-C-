This program takes a Boolean expression and evaluates it to determine if it is true or false. This does so using an abstract syntax tree as well as utilizing recursive decent for the parsing of the expressions.

The entirety of the program is based on Backus–Naur form(BNF), which you can read more about here: https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form

The valid inputs are, in any combination: "T", "F", "^", "v", "~", "=>", "<=>", "(", ")"

Some examples of valid inputs are below: T => F
T v F ^ F ~ F ^ T T v F ^ F ( (T ^ (~ (F v ~ T)))) T <=> F <=>

Some of the rules this follows: NOTE: A Boolean constant is ["T"] or ["F"]. An unbreakable expression is either a Boolean constant, or ["("] followed by a Boolean expression followed by [")"]. A negation is either an unbreakable expression, or ["~"] followed by a negation. A conjunction is either a negation, or a conjunction followed by ["^"] followed by a negation. A disjunction is either a conjunction, or a disjunction followed by ["v"] followed by a conjunction. An implication is either a disjunction, or a disjunction followed by ["=>"] followed by an implication. A Boolean expression is either an implication, or an implication followed by ["<=>"] followed by a Boolean expression.

Or in more simpler terms: Const → "T" | "F" U → Const | "(" B ")" N → U | "~" N C → N | C "^" N D → C | D "v" C
I → D | D "=>" I B → I | I "<=>" B
