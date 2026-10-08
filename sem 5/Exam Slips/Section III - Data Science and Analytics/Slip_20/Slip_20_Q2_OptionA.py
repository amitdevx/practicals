import pandas as pd
import matplotlib.pyplot as plt
from matplotlib_venn import venn2
from wordcloud import WordCloud
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Book Title': ['Data Science Basics', 'Advanced Python', 'Machine Learning', 'AI Future'],
    'Author': ['A. Smith', 'B. Jones', 'A. Smith', 'C. Lee'],
    'Publication Year': [2015, 2018, 2021, 2022],
    'Average Rating': [4.5, 4.2, 4.8, 4.6],
    'Number of Ratings': [100, 150, 200, 50]
})

period1 = set(df[df['Publication Year'] < 2020]['Author'])
period2 = set(df[df['Publication Year'] >= 2020]['Author'])

plt.figure()
venn2([period1, period2], set_labels=('Before 2020', '2020 and After'))
plt.title('Authors by Publication Period')
plt.savefig('books_venn.png')

text = " ".join(df['Book Title'])
wordcloud = WordCloud(width=400, height=200, background_color='white').generate(text)

plt.figure()
plt.imshow(wordcloud, interpolation='bilinear')
plt.axis('off')
plt.title('Word Cloud of Book Titles')
plt.savefig('books_wordcloud.png')
print("Plots saved.")
