# Domain (Variables)
people = ["Alice", "Bob", "Charlie", "David"]

# Predicates
students = {"Alice", "Bob"}
def is_student(person):
    return person in students

loves_ai_set = {"Alice", "Bob", "Charlie"}
def loves_ai(person):
    return person in loves_ai_set

print("\nPredicate Logic\n")
# Universal Quantifier (∀): For All x, if is_student(x) then loves_ai(x)
all_students_love_ai = all(loves_ai(p) for p in people if is_student(p))
print(f"Universal Quantifier (∀): Do all students love AI? {all_students_love_ai}")

# Existential Quantifier (∃): There Exists x, such that is_student(x) and loves_ai(x)
some_student_loves_ai = any(is_student(p) and loves_ai(p) for p in people)
print(f"Existential Quantifier (∃): Does any student love AI? {some_student_loves_ai}")
