import pandas as pd

vocabulary = {}
data = pd.read_csv("data/emails.csv")

def build_vocabulary(curr_email):
    idx = len(vocabulary)
    for word in curr_email:
        if word not in vocabulary:
            vocabulary[word] = idx
            idx += 1


if __name__ == "__main__":
    for i in range(data.shape[0]):
        curr_email = data.iloc[i, :][0].split()
        build_vocabulary(curr_email)

# Write dictionary to vocabulary.txt file
file = open("vocabulary.txt", "w")
file.write(str(vocabulary))
file.close()
