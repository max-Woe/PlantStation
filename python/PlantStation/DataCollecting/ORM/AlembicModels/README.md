#HANDLING OF ALEMBIC MODELS

## How to handle the alembic models:

This is a short overview how to handle the alembic models.

All Models are collected in Models.py, so they can share their Base. (The Base class collets data and metadata for handling the database)

- Every model represents a table in the database.
  - Every model must inherit from Base, to be known as part of the migration.

      Example model for a table in an explicit schema:
  ```python
    from datetime import datetime
    from sqlalchemy.orm import Mapped, declarative_base, mapped_column
    
    Base = declarative_base()
    
    #if an explicit schema is needed, else the following row is not needed.
    Base.metadata.schema = 'schema_name'  
    
    class ExampleModel(Base):
    __tablename__ = 'example_table'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    value: Mapped[float]
    description: Mapped[String]

    def __repr__(self):
            return f"id: {self.id}, vlaue: {self.value}, description: {self.description}"
    ```

- Base has to be imported into env.py and use it as metadata source:
    ```python
    from DataCollecting.ORM.AlembicModels.Models import Base
    ```
    ```python
    target_metadata = Base.metadata
    ```
  
create a new migration (in terminal): 
````text
alembic  revision --autogenerate -m "insert here ur migration message" 
````
run a new migration (in terminal):
````text
alembic upgrade head
````