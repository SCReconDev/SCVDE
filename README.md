# SCVDE – Local Setup

SCVDE compares static-analysis tools and ML models against vulnerability datasets. The project contains a FastAPI backend and a React/Vite frontend.


## 1. Install system packages

SCVDE was tested with Ubuntu 24.04

Install Python 3.12, `pipx`, build tools, and the C/C++ analyzers used by SCVDE.

```bash
sudo apt update
sudo apt install -y \
  git curl wget unzip ca-certificates build-essential \
  python3.12 python3.12-venv python3.12-dev pipx \
  cppcheck clang clang-tidy
```

Install git LFS

```bash
git install LFS
```

Clone the repository:

```bash
git clone https://github.com/SCReconDev/SCVDE.git
```

## 2. Install security tools

Install the security tools with `pipx`. 

```bash
pipx install semgrep
pipx install bandit
pipx install ruff
pipx install flawfinder
```
```bash
pipx ensurepath
export PATH="$HOME/.local/bin:$PATH"
```

Verify the installations:

```bash
semgrep --version
bandit --version
ruff --version
flawfinder --version
cppcheck --version
clang --version
clang-tidy --version
```

## 3. Install CodeQL

Download the CodeQL bundle and expose the `codeql` command system-wide (also outside of venv).

```bash
cd /tmp
curl -L -o codeql-bundle-linux64.tar.gz \
  https://github.com/github/codeql-action/releases/latest/download/codeql-bundle-linux64.tar.gz

sudo rm -rf /opt/codeql-bundle
sudo mkdir -p /opt/codeql-bundle
sudo tar -xzf codeql-bundle-linux64.tar.gz -C /opt/codeql-bundle
sudo ln -sf /opt/codeql-bundle/codeql/codeql /usr/local/bin/codeql

codeql version
codeql resolve packs
```

## 4. Install Node.js 22

The frontend uses Node.js and npm. NVM keeps the Node installation local to your user account.

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.5/install.sh | bash

export NVM_DIR="$HOME/.nvm"
. "$NVM_DIR/nvm.sh"

nvm install 22
nvm use 22
nvm alias default 22

node --version
npm --version
```

## 5. Set up the backend

Create a virtual environment and install the Python dependencies in the project root.

```bash
python3.12 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r backend/requirements.txt
```


Check the stored data and available detectors from the backend directory:

```bash
python -m app.cli storage info
python -m app.cli datasets list
python -m app.cli models list
python -m app.cli detectors list
```

Start the backend API in Backend directory with active venv:

```bash
uvicorn app.main:app 
```

## 6. Set up and start the frontend

Run these commands in a second terminal. `npm ci` must be executed inside `frontend`, where `package-lock.json` is located.

```bash
export NVM_DIR="$HOME/.nvm"
. "$NVM_DIR/nvm.sh"
nvm use 22
```

In Frontend directory:  
```bash
rm -rf node_modules dist
npm ci
npm run dev
```

Open the URL printed by Vite, normally `http://localhost:5173`.


## 7. Generate a dataset with Mistral. 

First create a Mistral API key 
Create an account in Mistral AI an log in. 
Then got to your profile on the upper right corner. 
Then go to API Key and create a new key. 

After creating the key execute the following command: 

```bash
export MISTRAL_API_KEY="Your API key"
```
Create a C dataset from the backend folder with active venv:

```bash
python -m app.cli datasets generate-mistral \
  --id mistral_memory_safety_test \
  --name "Mistral Memory Safety" \
  --vulnerability memory_safety \
  --language c \
  --num-vulnerable 500 \
  --num-safe 500 \
  --batch-size 10 \
  --overwrite
  ```


## 8. Test vulnerability detectors


```bash
python -m app.cli runs execute  \
  --dataset mistral_memory_safety_test \
  --detector cppcheck \
  --detector semgrep   \
  --detector flawfinder \
  --detector clang_static_analyzer \
  --detector clang_tidy_security \
  --detector hf_securebert2_vuln \
  --detector hf_graphcodebert_devign \
  --detector hf_codebert_devign
 ```
