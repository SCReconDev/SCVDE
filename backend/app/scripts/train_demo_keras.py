import yaml
import tensorflow as tf
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences

from app.config import settings


def main():
    model_id = "keras_demo_sqlinj"
    model_dir = settings.models_dir / model_id
    model_dir.mkdir(parents=True, exist_ok=True)

    texts = [
        '"SELECT * FROM users WHERE id = " + user_id',
        'f"SELECT * FROM users WHERE name = {name}"',
        '"SELECT * FROM users WHERE id = ?" cursor.execute(query, (user_id,))',
        '"SELECT * FROM users WHERE name = ?" cursor.execute(query, (name,))',
    ]

    labels = [1, 1, 0, 0]

    max_words = 1000
    max_length = 64

    tokenizer = Tokenizer(num_words=max_words, oov_token="<OOV>")
    tokenizer.fit_on_texts(texts)

    sequences = tokenizer.texts_to_sequences(texts)
    padded = pad_sequences(
        sequences,
        maxlen=max_length,
        padding="post",
        truncating="post",
    )

    model = tf.keras.Sequential(
        [
            tf.keras.layers.Embedding(max_words, 16, input_length=max_length),
            tf.keras.layers.GlobalAveragePooling1D(),
            tf.keras.layers.Dense(8, activation="relu"),
            tf.keras.layers.Dense(1, activation="sigmoid"),
        ]
    )

    model.compile(
        optimizer="adam",
        loss="binary_crossentropy",
        metrics=["accuracy"],
    )

    model.fit(
        padded,
        tf.constant(labels),
        epochs=20,
        verbose=0,
    )

    model.save(model_dir / "model.keras")

    tokenizer_json = tokenizer.to_json()
    (model_dir / "tokenizer.json").write_text(tokenizer_json, encoding="utf-8")

    config = {
        "id": model_id,
        "name": "Demo Keras SQL Injection Detector",
        "backend": "keras",
        "task": "binary_classification",
        "vulnerability_type": "sql_injection",
        "paths": {
            "model": "model.keras",
            "tokenizer": "tokenizer.json",
        },
        "input": {
            "max_length": max_length,
            "padding": "post",
            "truncating": "post",
        },
        "output": {
            "threshold": 0.5,
        },
    }

    with (model_dir / "model.yaml").open("w", encoding="utf-8") as f:
        yaml.safe_dump(config, f, sort_keys=False)



if __name__ == "__main__":
    main()