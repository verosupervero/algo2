flycombi: FlyCombi.py Grafo flycombi
	python -m venv env
	source env/bin/activate
	pip install -r requirements.txt
	cp FlyCombi.py flycombi
	chmod +x flycombi
