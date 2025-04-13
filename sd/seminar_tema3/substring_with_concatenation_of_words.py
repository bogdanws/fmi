class Solution:
    def findSubstring(self, s, words):
        word_len = len(words[0])
        word_count = len(words)
        total_len = word_len * word_count
        result = []
        
        word_counter = {}
        for word in words:
            word_counter[word] = word_counter.get(word, 0) + 1
        
        for i in range(len(s) - total_len + 1):
            seen = {}
            valid = True
            
            for j in range(word_count):
                start_idx = i + j * word_len
                current_word = s[start_idx:start_idx + word_len]
                
                if current_word not in word_counter:
                    valid = False
                    break
                
                seen[current_word] = seen.get(current_word, 0) + 1
                
                if seen[current_word] > word_counter[current_word]:
                    valid = False
                    break
            
            if valid:
                result.append(i)
        
        return result
        