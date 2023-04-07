#### 读取excel表格
```python
"""
功能说明：
将列[本地模块]中的'.' 去掉，生成一个新的列[本地模块_]
"""

import sys
import pandas as pd

def op(value):
    if value != value:
        return ""
    if value is None:
        return ""
    if len(value.strip()) == 0:
        return ""
    return value.replace('.', '')

def main(file_name):
    """注意：默认读取第一张sheet，表头是第一行"""
    df = pd.read_excel(file_name)
    df["本地模块_"] = df['本地模块'].apply(op)
    df['远程模块_'] = df["远程模块"].apply(op)
    df.to_excel(file_name, index=False)

main(sys.argv[1])
```

#### 保存为excel表格
```python
# data的数据结构：
# [["name1", "des1", "detail1", "sol1"],
#  ["name1", "des1", "detail1", "sol1"], ...]

# 设置表头
xml = data.DataFrame(data_df, columns=['name', 'description', 'detail', 'solution'], )

# 保存到文件
xml.to_excel("./env_check_config.xls", encoding='utf-8', index=False)
```

