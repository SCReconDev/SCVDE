from app.storage.file_store import FileStore


def main():
    store = FileStore()

    dataset_id = "demo_sqlinj"

    dataset = store.create_dataset(
        dataset_id=dataset_id,
        name="Demo SQL Injection Dataset",
        language="python",
        vulnerability_types=["sql_injection"],
        overwrite=True,
    )

    snippets = [
        {
            "id": "snippet_001",
            "filename": "snippet_001.py",
            "is_vulnerable": True,
            "expected_vulnerable_lines": [2],
            "code": '''def get_user(cursor, user_id):
    query = "SELECT * FROM users WHERE id = " + user_id
    return cursor.execute(query)
''',
        },
        {
            "id": "snippet_002",
            "filename": "snippet_002.py",
            "is_vulnerable": False,
            "expected_vulnerable_lines": [],
            "code": '''def get_user(cursor, user_id):
    query = "SELECT * FROM users WHERE id = ?"
    return cursor.execute(query, (user_id,))
''',
        },
        {
            "id": "snippet_003",
            "filename": "snippet_003.py",
            "is_vulnerable": True,
            "expected_vulnerable_lines": [2],
            "code": '''def search_users(cursor, name):
    query = f"SELECT * FROM users WHERE name = '{name}'"
    return cursor.execute(query)
''',
        },
        {
            "id": "snippet_004",
            "filename": "snippet_004.py",
            "is_vulnerable": False,
            "expected_vulnerable_lines": [],
            "code": '''def search_users(cursor, name):
    query = "SELECT * FROM users WHERE name = ?"
    return cursor.execute(query, (name,))
''',
        },
    ]

    dataset["snippets"] = []

    for item in snippets:
        relative_path = store.save_snippet_code(
            dataset_id=dataset_id,
            filename=item["filename"],
            code=item["code"],
        )

        dataset["snippets"].append(
            {
                "id": item["id"],
                "file_path": relative_path,
                "language": "python",
                "vulnerability_type": "sql_injection",
                "cwe": "CWE-89",
                "is_vulnerable": item["is_vulnerable"],
                "expected_vulnerable_lines": item["expected_vulnerable_lines"],
                "difficulty": "easy",
            }
        )

    store.save_dataset(dataset_id, dataset)

    print(f"Created demo dataset: {dataset_id}")
    print(f"Snippets: {len(dataset['snippets'])}")


if __name__ == "__main__":
    main()