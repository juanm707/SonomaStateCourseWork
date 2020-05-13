VENV=venv

check-port:
ifndef PORT
	$(error PORT environment variable is required)
endif

check-hostname:
ifndef HOSTNAME
	$(error HOSTNAME environment variable is required)
endif


.PHONY: $(VENV)
$(VENV):
	python3 -m venv $(VENV)
	$(VENV)/bin/python3 -m pip install -r requirements.txt

run_client: check-port check-hostname
	$(VENV)/bin/python3 connect4/client.py --hostname $(HOSTNAME) --port $(PORT)

run_server: check-port
	$(VENV)/bin/python3 connect4/server.py --port $(PORT)

itest: check-port
	$(VENV)/bin/python3 -m unittest discover -v connect4.test.integration -p "itest_client.py"

utest:
	$(VENV)/bin/python3 -m unittest -v
