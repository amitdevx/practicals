class KnowledgeGraph:
    def __init__(self):
        self.graph = {}

    def add_entity(self, entity):
        if entity not in self.graph:
            self.graph[entity] = []

    def add_relationship(self, subject, predicate, object_):
        self.add_entity(subject)
        self.add_entity(object_)
        self.graph[subject].append((predicate, object_))

    def display(self):
        print("\nSimple Knowledge Graph\n")
        for subject, relations in self.graph.items():
            for predicate, object_ in relations:
                print(f"{subject} --[{predicate}]--> {object_}")

kg = KnowledgeGraph()
kg.add_relationship("Alice", "knows", "Bob")
kg.add_relationship("Alice", "is interested in", "Artificial Intelligence")
kg.add_relationship("Bob", "studies", "Computer Science")
kg.add_relationship("Computer Science", "includes", "Artificial Intelligence")

kg.display()
