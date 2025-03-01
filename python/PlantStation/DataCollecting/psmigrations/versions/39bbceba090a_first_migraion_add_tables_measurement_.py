"""First migraion: add tables 'measurement', 'sensor', 'station' and trigger for sensor_reference in measurement

Revision ID: 39bbceba090a
Revises: 
Create Date: 2024-11-29 11:13:23.469951

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '39bbceba090a'
down_revision: Union[str, None] = None
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('measurement',
    sa.Column('id', sa.Integer(), autoincrement=True, nullable=False),
    sa.Column('value', sa.Float(), nullable=False),
    sa.Column('sensor_id', sa.Integer(), nullable=True),
    sa.Column('sensor_reference', sa.Integer(), nullable=False),
    sa.Column('recorded_at', sa.DateTime(), nullable=False),
    sa.Column('created_at', sa.DateTime(), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('sensor',
    sa.Column('id', sa.Integer(), autoincrement=True, nullable=False),
    sa.Column('type', sa.String(), nullable=False),
    sa.Column('unit', sa.String(), nullable=False),
    sa.Column('station_id', sa.Integer(), nullable=True),
    sa.Column('created_at', sa.DateTime(), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('station',
    sa.Column('id', sa.Integer(), autoincrement=True, nullable=False),
    sa.Column('position', sa.String(), nullable=False),
    sa.Column('sensors_count', sa.Integer(), nullable=False),
    sa.Column('created_at', sa.DateTime(), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )

    op.execute("""
        CREATE OR REPLACE FUNCTION set_sensor_reference()
        RETURNS TRIGGER AS $$
        BEGIN
            NEW.sensor_reference := NEW.sensor_id;  -- Setzt city_reference auf den Wert von city_id
            RETURN NEW;  -- Gibt den modifizierten Datensatz zurück
        END;
        $$ LANGUAGE plpgsql;
       """)

    op.execute("""
       CREATE TRIGGER trigger_set_sensor_reference
        BEFORE INSERT ON measurement  -- Ersetze 'measurement' mit dem tatsächlichen Namen deiner Tabelle
        FOR EACH ROW
        EXECUTE FUNCTION set_sensor_reference();
       """)
    # ### end Alembic commands ###


def downgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('station')
    op.drop_table('sensor')
    op.drop_table('measurement')

    op.execute("DROP TRIGGER IF EXISTS trigger_set_sensor_reference ON measurement")

    op.execute("DROP FUNCTION IF EXISTS set_sensor_reference")
    # ### end Alembic commands ###
