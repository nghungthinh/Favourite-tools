import csv 
import pandas as pd
import matplotlib.pyplot as plt

def ReadCsvFile(filename: str) -> pd.DataFrame:
    """
    Reads a CSV file and returns its contents as a pandas DataFrame.

    Args:
        filename (str): The name of the CSV file to read.

    Returns:
        pd.DataFrame: The contents of the CSV file as a DataFrame, with the first row
        containing the column names.
    """
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        data = list(reader)

    return pd.DataFrame(data[1:], columns=data[0])

def Write2CsvFile(filename: str, data: dict) -> bool:
    """
    Writes a DataFrame or dictionary to a CSV file.

    Args:
        filename (str): The name of the CSV file to write.
        data (dict): The data to write to the CSV file.
            If a dictionary is provided, it will be converted to a DataFrame.

    Returns:
        bool: True if the data was successfully written to the CSV file, False otherwise.
    """
    try:
        if not isinstance(data, pd.DataFrame):
            data = pd.DataFrame(data)

        with open(filename, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(data.columns)
            for _, row in data.iterrows():
                writer.writerow(row)

        return True
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    
"""
Write a Example for use of dumpFile.py

data = dict({
    'X': [],
    'Y': [],
    'Z': []})
Write:
    df.Write2CsvFile('test.csv', data)

Read:
    data = df.ReadCsvFile('test.csv')
"""