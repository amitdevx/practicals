class Animal:
    def __init__(self, name):
        self.name = name

    def description(self):
        return f"{self.name} is an animal."

class Mammal(Animal): # Subclass representing a relationship
    def __init__(self, name, legs):
        super().__init__(name)
        self.legs = legs

    def description(self):
        return f"{self.name} is a mammal with {self.legs} legs."

class Dog(Mammal): # Subclass representing a more specific relationship
    def bark(self):
        return "Woof!"

# Demonstrating Ontology
entity1 = Animal("Generic Creature")
entity2 = Mammal("Human", 2)
entity3 = Dog("Buddy", 4)

print("\nOntological Engineering Concepts\n")
print("Classes, Subclasses, and Relationships:\n")
print(f"Entity 1: {entity1.description()}")
print(f"Entity 2: {entity2.description()}")
print(f"Entity 3: {entity3.description()} It says: {entity3.bark()}")
print("\nRelationship: Dog IS-A Mammal IS-A Animal")
