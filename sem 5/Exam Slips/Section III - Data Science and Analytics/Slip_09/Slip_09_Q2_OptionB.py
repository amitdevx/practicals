import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib_venn import venn2
from wordcloud import WordCloud

data = {
    'Book_Title': ['Data Science Basics', 'Machine Learning Guide', 'Deep Learning Concepts', 'AI in Future', 'Python for All'],
    'Author': ['Alice', 'Bob', 'Alice', 'Charlie', 'Bob'],
    'Publication_Year': [1998, 2005, 2010, 2015, 1999],
    'Average_Rating': [4.5, 4.0, 4.8, 3.9, 4.2],
    'Number_of_Ratings': [100, 150, 200, 50, 300]
}
df = pd.DataFrame(data)

# Venn Diagram: Authors in Period 1 (<=2000) vs Period 2 (>2000)
authors_p1 = set(df[df['Publication_Year'] <= 2000]['Author'])
authors_p2 = set(df[df['Publication_Year'] > 2000]['Author'])

plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
venn2([authors_p1, authors_p2], set_labels=('Before 2000', 'After 2000'))
plt.title('Authors by Publication Period')

# Word Cloud
plt.subplot(1, 2, 2)
text = ' '.join(df['Book_Title'])
wordcloud = WordCloud(width=400, height=300, background_color='white').generate(text)
plt.imshow(wordcloud, interpolation='bilinear')
plt.axis('off')
plt.title('Book Titles Word Cloud')

plt.tight_layout()
plt.savefig('books_analysis.png')
print("Saved books_analysis.png")
