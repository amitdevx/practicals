# Knowledge Base representation in Python
# Facts
knowledge_base = {
    "is_raining": True,
    "has_umbrella": False
}

# Rules
def rule1(kb):
    if kb.get("is_raining") and not kb.get("has_umbrella"):
        return "You will get wet."
    return None

def rule2(kb):
    if kb.get("is_raining") and kb.get("has_umbrella"):
        return "You will stay dry."
    return None

print("\nSimple Knowledge Base\n")
print("Facts:", knowledge_base)

result1 = rule1(knowledge_base)
if result1:
    print("Inference 1:", result1)

result2 = rule2(knowledge_base)
if result2:
    print("Inference 2:", result2)
