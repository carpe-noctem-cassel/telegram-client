from flair.data import Sentence
from flair.models import SequenceTagger
import sys 

# load the NER tagger
tagger = SequenceTagger.load('ner')

# Iteration over command lines
for arg in sys.argv:
	# make a sentence
	sentence = Sentence(arg)
	
	# run NER over sentence
	tagger.predict(sentence)
        
	print(sentence)
	print('The following NER tags are found:')

	# iterate over entities and print
	for entity in sentence.get_spans('ner'):
    		print(entity)

