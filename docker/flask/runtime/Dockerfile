ARG IMAGE_NAME
FROM ${IMAGE_NAME}:base

COPY python /arctern/python

RUN cd /arctern/python && \
    python3.7 -m pip --no-cache-dir install --upgrade cython pyarrow && \
    python setup.py build build_ext --issymbol && \
    python setup.py install && \
    cd / && rm -rf /arctern/python

COPY spark /arctern/spark

RUN cd /arctern/spark/pyspark && \
    python setup.py build && \
    python setup.py install && \
    cd / && rm -rf /arctern/spark

COPY gui/server /arctern/gui/server

RUN cd /arctern/gui/server && \
    python3.7 -m pip --no-cache-dir install -r requirements.txt

EXPOSE 8080

WORKDIR /arctern/gui/server

# use login shell when running the container
CMD ["python", "manage.py", "-r"]
