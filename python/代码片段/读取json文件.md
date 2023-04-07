```python
import json

# 打开文件
with open("file.json", 'r', encoding='utf-8') as f:
    json_content = json.load(f)

# 读取到内存
data = []
for ele in json_content:
    data.append([ele['key1'], ele['key1'], ele['key1'], ele['key1']])
```

