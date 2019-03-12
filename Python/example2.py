from flair.data import Sentence
from flair.models import SequenceTagger
import sys
from flair.embeddings import WordEmbeddings, FlairEmbeddings, StackedEmbeddings

# create a StackedEmbedding object that combines glove and forward/backward flair embeddings
stacked_embeddings = StackedEmbeddings([
                                        WordEmbeddings('glove'), 
                                        FlairEmbeddings('news-forward'), 
                                        FlairEmbeddings('news-backward'),
                                       ])

# load the NER tagger
tagger = SequenceTagger.load('ner')

# Iteration over command lines
for arg in sys.argv:
	# make a sentence
	sentence = Sentence(arg)

	# just embed a sentence using the StackedEmbedding as you would with any single 	embedding.
	stacked_embeddings.embed(sentence)

	# now check out the embedded tokens.
	for token in sentence:
    		print(token)
    		print(token.embedding)

